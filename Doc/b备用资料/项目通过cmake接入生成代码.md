我制作了代码生成工具, 如何用cmake实现生成的代码加到对应模块的源码进行编译, 同时模块的工程不需要因为增加或减少了生成的代码而重新生成

AI

要在 CMake 中集成代码生成工具，使生成的代码可以被编译而又不影响模块的工程结构，您可以采用以下步骤：

1. **创建生成代码的 CMake 脚本**：您需要一个 CMake 函数或宏，负责调用您的代码生成工具并将生成的代码添加到工程中。
2. **生成目录**：您可以指定一个输出目录用于存放生成的代码，这样可以将生成代码和原始源码分开管理。
3. **使用 CMake 的配置检查**：通过检查生成代码的文件更新时间，决定是否需要重新生成代码。您可以使用 `add_custom_command` 和 `add_custom_target` 来实现。
4. **将生成的代码添加到源文件列表中**：最后，您需要将那些生成的代码文件添加到要编译的目标中。

下面是一个示例的 CMakeLists.txt 文件，展示如何实现上述步骤：

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 定义生成代码的目录
set(GENERATED_CODE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_code")

# 定义生成代码的输出文件
set(GENERATED_CODE_FILE "${GENERATED_CODE_DIR}/generated.cpp")

# 确保生成目录存在
file(MAKE_DIRECTORY ${GENERATED_CODE_DIR})

# 添加自定义命令，调用代码生成工具
add_custom_command(
    OUTPUT ${GENERATED_CODE_FILE}
    COMMAND my_code_generator_tool --output ${GENERATED_CODE_FILE}
    DEPENDS my_code_generator_tool  # 依赖于生成工具
    COMMENT "Generating code..."
)

# 创建一个自定义目标，做为代码生成的依赖
add_custom_target(GenerateCode ALL DEPENDS ${GENERATED_CODE_FILE})

# 将生成的代码文件添加到可执行目标或库
add_executable(MyExecutable main.cpp ${GENERATED_CODE_FILE})

# 如果需要其他源文件，可以继续添加
# add_executable(MyExecutable main.cpp other_source.cpp ${GENERATED_CODE_FILE})
```

### 说明：

1. `add_custom_command` 用于指定生成文件的命令。该命令会在输出文件不存在或是过期的情况下被执行。
2. `add_custom_target` 用于创建一个虚拟目标 `GenerateCode`，使其在你构建项目时会自动触发。
3. `${GENERATED_CODE_FILE}` 被添加到目标（这里是 `MyExecutable`）中。这样编译时会自动包含这些生成的代码。

### 对于代码的添加和删除：

如果生成的代码数量变化（增加或减少），您无需手动修改 CMakeLists.txt，代码生成工具会负责生成正确的文件。CMake 在构建时会智能地处理这些变动。

确保您的代码生成工具在文件发生更改时会更新相应的输出文件。如果将生成过程和编译过程在物理上分离，且合理使用 CMake 的依赖管理，就能在一定程度上满足您提到的需求。



要求 my_code_generator_tool 实现对生成代码的编译功能吗, 还是只需要生成代码文件, 通过cmake的虚拟目标实现在构建时先对生成的代码编译?

AI

在你的场景中，`my_code_generator_tool` 主要的责任是生成代码文件，而不是直接实现代码的编译功能。CMake 的角色是通过配置构建过程来管理这项工作。这样可以确保生成的代码在每次构建时自动编译，而不需要对 CMake 配置文件进行频繁的修改。

### 简要总结：

1. **生成代码**：`my_code_generator_tool` 只负责生成代码文件。
2. **管理编译**：使用 CMake 的机制来管理生成的代码文件的编译，而不需要重新生成整个 CMake 工程。

### 示例 CMakeLists.txt 的实现：

下面是一个实例，展示如何实现这一点，同时避免因生成的代码数量变化而重新运行 CMake 配置。

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 定义生成代码的目录和输出文件
set(GENERATED_CODE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_code")
set(GENERATED_CODE_FILE "${GENERATED_CODE_DIR}/generated.cpp")

# 确保生成目录存在
file(MAKE_DIRECTORY ${GENERATED_CODE_DIR})

# 使用 CMake 的自定义命令来生成代码
add_custom_command(
    OUTPUT ${GENERATED_CODE_FILE}
    COMMAND my_code_generator_tool --output ${GENERATED_CODE_FILE}
    DEPENDS my_code_generator_tool  # 标明依赖于代码生成工具
    COMMENT "Generating code..."
)

# 创建一个自定义目标，确保在构建时生成功能生效
add_custom_target(GenerateCode ALL DEPENDS ${GENERATED_CODE_FILE})

# 添加可执行目标，同时包含生成的代码
add_executable(MyExecutable main.cpp ${GENERATED_CODE_FILE})

# 如果需要添加更多的源文件，可以继续添加
# add_executable(MyExecutable main.cpp other_source.cpp ${GENERATED_CODE_FILE})
```

### 运行机制的说明：

1. **生成代码**：当你执行构建时，CMake 将检查生成的代码文件是否存在或是否过期。如果不存在或者依赖的输入文件发生变化，CMake 将执行定义在 `add_custom_command` 中的命令，生成新的源代码文件。
2. **编译生成的代码**：生成的代码文件 `generated.cpp` 将自动包括在 `MyExecutable` 的构建中。CMake 会处理将它们传递到编译器的步骤。
3. **不重新生成 CMake 构建**：由于生成的代码是在构建时处理的，而不依赖于你修改 CMakeLists.txt，因此如果生成的代码发生增加或减少，只要驱动代码生成工具生成相应的文件，CMake 不会因为这些变化而要求重新配置项目。

### 总结：

使用这种方法，你可以在构建流程中方便地管理生成的代码，同时维护一个相对稳定的 CMake 配置。这样，代码生成的更新不会频繁干扰开发流程，也保持了代码的模块化和清晰性。



--output 所演示的, 传入 my_code_generator_tool 的 ${GENERATED_CODE_FILE} 变量, 对应的内容是什么样的格式, 如何在工具中解析

AI

如果您的代码生成工具接受一个 `--output` 参数，通常这个参数指定了工具生成的代码的输出文件路径。在工具内部，您需要解析该路径，并将生成的代码写入对应的文件。下面是一个实现的示例，包括生成的代码格式，也包括如何在工具中解析这些参数。

### 1. 示例代码生成工具

假设您的代码生成工具是一个简单的可执行文件，使用 C++ 编写。您可以使用命令行参数来指定输出文件的路径。以下是一个简单的实现示例：

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void generateCode(const std::string& outputPath) {
    // 生成代码内容，可以根据实际需求调整
    std::string codeContent = R"(
    // 自动生成的代码
    #include <iostream>

    void generatedFunction() {
        std::cout << "This code was generated!" << std::endl;
    }
    )";

    // 将生成的代码写入指定文件
    std::ofstream outputFile(outputPath);
    if (!outputFile) {
        std::cerr << "Error: Could not open output file " << outputPath << std::endl;
        return;
    }

    outputFile << codeContent;
    outputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3 || std::string(argv[1]) != "--output") {
        std::cerr << "Usage: " << argv[0] << " --output <output_file>" << std::endl;
        return 1;
    }

    std::string outputPath = argv[2];
    generateCode(outputPath);

    return 0;
}
```

### 2. CMakeLists.txt 的使用

在您的 CMake 项目中，您可以像之前提到的那样集成这个工具，以便在构建时生成代码。确保在 CMake 配置中指定生成路径。以下是一个示例：

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 定义生成代码的目录
set(GENERATED_CODE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_code")

# 定义生成代码的输出文件
set(GENERATED_CODE_FILE "${GENERATED_CODE_DIR}/generated.cpp")

# 确保生成目录存在
file(MAKE_DIRECTORY ${GENERATED_CODE_DIR})

# 添加自定义命令，调用代码生成工具
add_custom_command(
    OUTPUT ${GENERATED_CODE_FILE}
    COMMAND my_code_generator_tool --output ${GENERATED_CODE_FILE}
    DEPENDS my_code_generator_tool  # 依赖于生成工具
    COMMENT "Generating code..."
)

# 创建一个自定义目标，做为代码生成的依赖
add_custom_target(GenerateCode ALL DEPENDS ${GENERATED_CODE_FILE})

# 将生成的代码文件添加到可执行目标
add_executable(MyExecutable main.cpp ${GENERATED_CODE_FILE})

# 如果需要其他源文件，可以继续添加
# add_executable(MyExecutable main.cpp other_source.cpp ${GENERATED_CODE_FILE})
```

### 3. 解析和使用参数

在工具的 `main` 函数中，通过 `argv` 数组获取命令行参数，您可以轻松地解析不同的输入。这里的 `argv[1]` 是 `--output`，而 `argv[2]` 是您希望生成的输出文件的路径。

### 4. 生成的代码格式

生成的代码内容可以根据您项目的需求而变化。上面的示例创建了一个简单的 C++ 函数，这个函数在运行时会输出一行信息。您可以根据需要生成更复杂的代码结构和内容。

### 小结

通过以上方法，您可以使用 `my_code_generator_tool` 生成代码，并方便地将这些代码整合到 CMake 项目中，而不需要对模块的 CMake 配置进行频繁的修改。当代码生成工具产生的文件变化时，只要运行构建命令，CMake 将会处理新生成的代码，确保它们能够被正确编译。



但是生成的代码文件通常是通过 file(GLOB_RECURSE GeneratedSrc ${GeneratedSrcPath}/*.cpp ${GeneratedSrcPath}/*.h) 收集的, 这种情况应如何传入工具

AI

如果你的 `my_code_generator_tool` 需要根据某些输入文件（例如特定目录中的 `.cpp` 和 `.h` 文件）生成代码，那么可以通过 CMake 中的目标（target）机制以及 CMake 的自定义命令（add_custom_command）来处理这些文件。具体步骤如下：

### 1. 生成源文件列表

首先，使用 `file(GLOB_RECURSE ...)` 收集所有需要的源文件。这些文件将作为输入传递给代码生成工具。

```cmake
# 定义生成源文件的路径
set(GeneratedSrcPath "${CMAKE_CURRENT_SOURCE_DIR}/generated_src")

# 收集源文件
file(GLOB_RECURSE GeneratedSrc ${GeneratedSrcPath}/*.cpp ${GeneratedSrcPath}/*.h)
```

### 2. 生成代码文件并传入所需的输入文件

然后，可以通过 `add_custom_command` 来调用 `my_code_generator_tool`，将收集到的源文件作为参数传递给工具。这里，你可以使用 CMake 的引号扩展来处理空格和特殊字符：

```cmake
# 定义生成的代码文件路径
set(GENERATED_CODE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_code")
set(GENERATED_CODE_FILE "${GENERATED_CODE_DIR}/generated.cpp")

# 确保生成目录存在
file(MAKE_DIRECTORY ${GENERATED_CODE_DIR})

# 使用 CMake 的自定义命令生成代码
add_custom_command(
    OUTPUT ${GENERATED_CODE_FILE}
    COMMAND my_code_generator_tool --output ${GENERATED_CODE_FILE} ${GeneratedSrc}
    DEPENDS ${GeneratedSrc} # 依赖于收集的源文件
    COMMENT "Generating code..."
)
```

### 3. 创建自定义目标

创建一个自定义目标，使得在编译时会首先调用代码生成工具。这样，生成的代码文件将在项目 builds 时自动编译。

```cmake
# 创建自定义目标
add_custom_target(GenerateCode ALL DEPENDS ${GENERATED_CODE_FILE})

# 添加可执行目标，包含生成的代码
add_executable(MyExecutable main.cpp ${GENERATED_CODE_FILE})
```

### 4. 完整的 CMakeLists.txt 示例

下面是一个集成上述步骤的完整 CMakeLists.txt 示例：

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 定义生成源文件的路径
set(GeneratedSrcPath "${CMAKE_CURRENT_SOURCE_DIR}/generated_src")

# 收集源文件
file(GLOB_RECURSE GeneratedSrc ${GeneratedSrcPath}/*.cpp ${GeneratedSrcPath}/*.h)

# 定义生成的代码文件的路径
set(GENERATED_CODE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_code")
set(GENERATED_CODE_FILE "${GENERATED_CODE_DIR}/generated.cpp")

# 确保生成目录存在
file(MAKE_DIRECTORY ${GENERATED_CODE_DIR})

# 使用 CMake 的自定义命令生成代码
add_custom_command(
    OUTPUT ${GENERATED_CODE_FILE}
    COMMAND my_code_generator_tool --output ${GENERATED_CODE_FILE} ${GeneratedSrc}
    DEPENDS ${GeneratedSrc} # 依赖于收集的源文件
    COMMENT "Generating code..."
)

# 创建自定义目标以在构建时生成代码
add_custom_target(GenerateCode ALL DEPENDS ${GENERATED_CODE_FILE})

# 添加可执行目标，包含生成的代码
add_executable(MyExecutable main.cpp ${GENERATED_CODE_FILE})
```

### 关键点总结

1. **处理文件收集**：使用 `file(GLOB_RECURSE ...)` 来收集源文件，并将这些文件传递给生成工具。
2. **自定义命令与目标**：通过 `add_custom_command` 和 `add_custom_target` 来确保在构建时生成代码，这样生成的代码将在编译阶段自动纳入编译流程中。
3. **依赖管理**：确保工具的输出与输入正确设置依赖，以便 CMake 在文件更改时自动重新生成和编译。

### 注意事项

- `my_code_generator_tool` 实际上只负责生成代码，而不是处理编译。CMake 负责管理构建过程。
- 如果 `my_code_generator_tool` 对输入文件有顺序依赖，请确保在传递文件时遵循所需顺序。
- 使用 CMake 的缓存或更新机制，避免不必要的重新生成。



${GeneratedSrc}的数据格式是什么样的, 如何解析

AI

在 CMake 中使用 `file(GLOB_RECURSE ...)` 收集文件时，`GeneratedSrc` 变量会包含一个由文件路径组成的列表，这些路径是匹配指定模式的所有文件。例如，执行以下 CMake 命令：

```cmake
file(GLOB_RECURSE GeneratedSrc ${GeneratedSrcPath}/*.cpp ${GeneratedSrcPath}/*.h)
```

如果 `GeneratedSrcPath` 中有三个 `.cpp` 文件和两个 `.h` 文件，`GeneratedSrc` 变量将包含如下内容：

```
path/to/source1.cpp
path/to/source2.cpp
path/to/source3.cpp
path/to/header1.h
path/to/header2.h
```

### 如何传入工具

可以直接将 `GeneratedSrc` 作为参数传递给你的代码生成工具。例如，如果你的代码生成工具可以接受多个文件作为输入，可以这样调用它：

```cmake
add_custom_command(
    OUTPUT ${GENERATED_CODE_FILE}
    COMMAND my_code_generator_tool --output ${GENERATED_CODE_FILE} ${GeneratedSrc}
    DEPENDS ${GeneratedSrc} # 确保工具依赖于源文件
    COMMENT "Generating code..."
)
```

### 关于 `${GeneratedSrc}` 的数据格式

在 CMake 中，`${GeneratedSrc}` 是以空格分隔的字符串，包含了所有收集到的文件路径。当你在 CMake 的 `COMMAND` 字段中使用 `${GeneratedSrc}` 时，它会自动展开为每个文件的路径。例如：

```cmake
# 模拟的生成源文件路径
set(GeneratedSrc "path/to/source1.cpp" "path/to/source2.cpp" "path/to/header1.h")
```

那么在 `add_custom_command` 中的 `COMMAND` 将具有如下效果：

```
my_code_generator_tool --output generated.cpp path/to/source1.cpp path/to/source2.cpp path/to/header1.h
```

### 如何解析 ${GeneratedSrc}

在 CMake 中，通常不需要手动解析 `${GeneratedSrc}`，因为它已经是经过 CMake 处理的文件列表，可以直接用作参数。然而，如果你想更灵活地处理这些路径，比如进行某种格式化或过滤，你可以使用 CMake 的循环结构，例如 `foreach`：

```cmake
foreach(source IN LISTS GeneratedSrc)
    message(STATUS "Found source file: ${source}")
endforeach()
```

### 总结

- `file(GLOB_RECURSE ...)` 收集的结果是一个空格分隔的文件路径列表。
- 可以直接将 `${GeneratedSrc}` 用于命令参数。
- CMake 会在处理 `COMMAND` 时自动展开 `${GeneratedSrc}`。

这样，您就可以使用生成的代码文件以及其他输入文件以最有效的方式调用工具。



我是问如何在我的生成工具中解析传入的 ${GeneratedSrc}

AI

理解了您的问题后，下面将详细说明如何在您的代码生成工具中解析传入的 `${GeneratedSrc}` 参数。

### 数据格式

在 CMake 中，`file(GLOB_RECURSE ...)` 收集的文件会被存储在一个变量中（如 `${GeneratedSrc}`），这个变量是一个以空格分隔的字符串。每个文件路径都是一个独立的字符串，因此在许多情况下，您可以将其直接传递给生成工具。

以下是一个示例：

```bash
# 传入格式为
my_code_generator_tool --output generated.cpp file1.cpp file2.cpp file3.h
```

在这个示例中，`file1.cpp`、`file2.cpp` 和 `file3.h` 都是源码文件的路径，它们通过空格分隔。

### 在生成工具中解析参数

在您的代码生成工具的实现中，您需要解析传入的命令行参数。以下是如何在一些常见编程语言中执行此操作的示例。

#### C++

如果您用 C++ 编写生成工具，可以使用 `argc` 和 `argv` 来解析命令行参数：

```cpp
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: my_code_generator_tool --output <output_file> <input_files...>\n";
        return 1;
    }

    std::string output_file;
    std::vector<std::string> input_files;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--output" && i + 1 < argc) {
            // 获取输出文件
            output_file = argv[++i];
        } else {
            // 其他参数视为输入文件
            input_files.push_back(arg);
        }
    }

    std::cout << "Output file: " << output_file << std::endl;
    std::cout << "Input files:" << std::endl;
    for (const auto& file : input_files) {
        std::cout << "  " << file << std::endl;
    }

    // 在这里添加您的代码生成逻辑

    return 0;
}
```

#### Python

如果您用 Python 编写生成工具，可以使用 `sys.argv` 来解析命令行参数：

```python
import sys

def main():
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} --output <output_file> <input_files...>")
        return

    output_file = None
    input_files = []

    i = 1
    while i < len(sys.argv):
        if sys.argv[i] == '--output':
            if i + 1 < len(sys.argv):
                output_file = sys.argv[i + 1]
                i += 2
            else:
                print("Error: Missing output file after --output")
                return
        else:
            input_files.append(sys.argv[i])
            i += 1

    print(f"Output file: {output_file}")
    print("Input files:")
    for file in input_files:
        print(f"  {file}")

    # 在这里添加您的代码生成逻辑

if __name__ == "__main__":
    main()
```

### 注意事项

1. **参数顺序**：确保调用时参数顺序正确，尤其是 `--output` 后必须跟着输出文件名。输入文件可以在输出文件之后的任何位置。
2. **错误处理**：在解析参数时，您应包括适当的错误处理，以确保生成工具在遇到无效参数时能够给出清晰错误信息。
3. **支持路径**：传入的文件路径应在生成工具内进行合理的处理，确保可以找到这些文件（如检查文件是否存在等）。

通过以上方法，您可以有效地解析 `file(GLOB_RECURSE ...)` 收集到的文件，并在您的代码生成工具中使用这些输入文件进行处理。































































































我制作了代码生成工具, 如何用cmake实现生成的代码加到对应模块的源码进行编译, 同时模块的工程不需要因为增加或减少了生成的代码而重新生成

AI

在 CMake 中实现代码生成的同时又不影响主模块工程的编译，可以采取以下方式：

1. **使用 CMake 的自定义命令**： 利用 CMake 的 `add_custom_command` 和 `add_custom_target` 来生成代码，并将生成的代码输出到一个指定的目录。
2. **将生成的代码包含在目标中**： 在主模块的 CMakeLists.txt 中添加相应的 `include_directories` 或 `target_sources` 指令，将生成的代码包括进来。
3. **避免重复构建**： 通过设置适当的依赖关系，使得生成的代码在文件没有变化时不触发重新编译。

下面是一个基本的示例来说明这一过程：

### 项目目录结构

```
/your_project/
├── CMakeLists.txt
├── src/
│   ├── module1.cpp
│   └── module1.h
├── generated/
│   └── generated_code.cpp
└── tools/
    ├── code_generator.cpp
    └── CMakeLists.txt
```

### 顶层 CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(YourProject)

# 指定源文件和头文件
add_subdirectory(src)
add_subdirectory(tools)
```

### src/CMakeLists.txt

```cmake
add_library(module1 src/module1.cpp src/module1.h)

# 添加生成的代码
file(GLOB_RECURSE GENERATED_CODE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../generated/*.cpp")

# 如果没有生成代码，则过滤，避免多余的编译
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../generated/")
    target_sources(module1 PRIVATE ${GENERATED_CODE_FILES})
endif()
```

### tools/CMakeLists.txt

```cmake
# 设置这个工具的可执行文件
add_executable(code_generator code_generator.cpp)

# 自定义命令生成代码
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../generated/generated_code.cpp
    COMMAND ${CMAKE_COMMAND} -E echo "Generating code..." # 替换为实际生成代码的命令
    DEPENDS code_generator
)

# 创建一个自定义目标，用于生成代码
add_custom_target(generate ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../generated/generated_code.cpp)
```

### 说明：

1. **code_generator** 编译后的可执行文件可以用于代码生成。
2. **add_custom_command** 是在每次 `generate` 目标构建时执行的，而 `OUTPUT` 设定了生成的文件。
3. 在 `src/CMakeLists.txt` 中，使用 `file(GLOB_RECURSE ...)` 来查找生成的 `.cpp` 文件，并将其添加到 `module1` 的编译目标中。
4. 通过 `${CMAKE_CURRENT_SOURCE_DIR}/../generated/` 判定生成的代码目录是否存在，并且在存在时再加入到 `module1` 的编译。

这种方式可以有效地将生成的代码集成到你的项目中，并避免因代码的增加或删除而重新生成其他模块的过程。注意，你可以根据实际的生成过程调整 `COMMAND` 部分的内容。



这样实现, 生成的代码会被加到如VS的工程中吗, 我不希望生成的代码被加到vs工程中

AI

为了在 CMake 中生成代码并将其编译到模块中，同时确保生成的代码不会在 Visual Studio 等 IDE 中显示，您可以采取以下措施：

1. **使用自定义命令生成代码**，但不把生成的文件直接添加到目标的源文件列表中，而是将其放入一个专门的构建目录中。
2. **通过条件编译**或设置标志来控制代码的编译。

下面是一个示例，展示如何实现这一过程：

### 1. 项目结构

```
/your_project/
├── CMakeLists.txt
├── src/
│   ├── module1.cpp
│   └── module1.h
├── generated/
│   └── generated_code.cpp  # 这个文件不会被直接添加到工程中
└── tools/
    ├── code_generator.cpp
    └── CMakeLists.txt
```

### 2. 顶层 `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.10)
project(YourProject)

# 指定模块的源路径
add_subdirectory(src)
add_subdirectory(tools)
```

### 3. `src/CMakeLists.txt`

在这里，我们添加生成的代码，但不直接将其包括在 IDE 项目中，通过条件编译来处理。

```cmake
# 创建库或可执行文件
add_library(module1 src/module1.cpp src/module1.h)

# 生成代码的输入和输出路径
set(GENERATED_CODE_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_CODE_DIR})
set(GENERATED_CODE_FILE "${GENERATED_CODE_DIR}/generated_code.cpp")

# 如果需要检查代码生成是否需要重新生成，参考以下代码
add_custom_command(
    OUTPUT ${GENERATED_CODE_FILE}
    COMMAND ${CMAKE_COMMAND} -E echo "Generating code..."
    DEPENDS code_generator   # 依赖于代码生成工具
)

# 添加目标，但不添加到显示的源码中
add_custom_target(generate_code ALL DEPENDS ${GENERATED_CODE_FILE})

# 将生成的代码包含到编译过程中，但不直接在 IDE 中显示
target_sources(module1 PRIVATE ${GENERATED_CODE_FILE})
```

### 4. `tools/CMakeLists.txt`

```cmake
# 定义代码生成工具
add_executable(code_generator code_generator.cpp)

# 自定义命令，生成代码
add_custom_command(
    TARGET code_generator
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Code generation complete."
)

# 使 generate_code 目标依赖于此工具的成果（可选改善）
add_dependencies(generate_code code_generator)
```

### 说明

1. **GENERATED_CODE_DIR**: 生成的代码文件保存在构建目录中，而不是源代码目录中，减少对源代码的污染。
2. **target_sources**: 使用 `PRIVATE` 将生成的文件添加到模块中，这样它不会显示在 Visual Studio 的项目文件中，避免直接依赖这个文件。
3. **自定义命令**: 通过 `add_custom_command` 和 `add_custom_target` 来控制代码生成，并确保运行生成器。

这个结构保证了生成的代码不会影响已有模块的编译，您可以用自定义的方式来控制生成和编译的过程，而不会在 IDE 中看到所有生成的代码文件。