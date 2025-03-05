以下是封装后的独立函数，通过显式参数返回获取的宏定义列表：

```cmake
# 用法：get_target_all_definitions(目标名 输出变量名)
function(get_target_all_definitions TARGET OUTPUT_VAR)
    # 有效性检查
    if(NOT TARGET ${TARGET})
        message(FATAL_ERROR "Target '${TARGET}' does not exist")
    endif()

    # 初始化存储容器
    set(ALL_DEFS)

    # 阶段1：获取目标的直接编译定义 ----------------------------
    get_target_property(TARGET_DEFS ${TARGET} COMPILE_DEFINITIONS)
    if(TARGET_DEFS AND NOT "${TARGET_DEFS}" STREQUAL "TARGET_DEFS-NOTFOUND")
        list(APPEND ALL_DEFS ${TARGET_DEFS})
    endif()

    # 阶段2：解析编译选项中的 -D 定义 ------------------------
    get_target_property(TARGET_OPTS ${TARGET} COMPILE_OPTIONS)
    if(TARGET_OPTS AND NOT "${TARGET_OPTS}" STREQUAL "TARGET_OPTS-NOTFOUND")
        foreach(OPT IN LISTS TARGET_OPTS)
            # 处理可能包含空格的定义（如"-DFOO=bar baz"）
            string(REPLACE " " ";" OPT_LIST ${OPT})
            foreach(SUBOPT IN LISTS OPT_LIST)
                if(SUBOPT MATCHES "^-D")
                    string(REGEX REPLACE "^-D" "" DEF ${SUBOPT})
                    list(APPEND ALL_DEFS ${DEF})
                endif()
            endforeach()
        endforeach()
    endif()

    # 阶段3：全局编译定义 ------------------------------------
    # 目录级定义
    get_directory_property(DIR_DEFS COMPILE_DEFINITIONS)
    if(DIR_DEFS)
        list(APPEND ALL_DEFS ${DIR_DEFS})
    endif()

    # 全局编译标志中的定义（如 CMAKE_CXX_FLAGS）
    string(REGEX MATCHALL "-D[^ ]+" GLOBAL_DEFS 
        "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")
    foreach(DEF_OPT IN LISTS GLOBAL_DEFS)
        string(REGEX REPLACE "^-D" "" DEF ${DEF_OPT})
        list(APPEND ALL_DEFS ${DEF})
    endforeach()

    # 阶段4：处理依赖项的接口定义 ----------------------------
    get_target_property(DEPS ${TARGET} LINK_LIBRARIES)
    if(DEPS AND NOT "${DEPS}" STREQUAL "DEPS-NOTFOUND")
        foreach(DEP IN LISTS DEPS)
            if(TARGET ${DEP})
                # 获取接口定义
                get_target_property(IFACE_DEFS ${DEP} INTERFACE_COMPILE_DEFINITIONS)
                if(IFACE_DEFS AND NOT "${IFACE_DEFS}" STREQUAL "IFACE_DEFS-NOTFOUND")
                    list(APPEND ALL_DEFS ${IFACE_DEFS})
                endif()
            endif()
        endforeach()
    endif()

    # 后处理：去重并设置结果 --------------------------------
    if(ALL_DEFS)
        list(REMOVE_DUPLICATES ALL_DEFS)
    endif()

    # 将结果传递到父作用域
    set(${OUTPUT_VAR} ${ALL_DEFS} PARENT_SCOPE)
endfunction()
```

### 使用示例

```cmake
# 定义测试目标
add_library(MyLib ...)
target_compile_definitions(MyLib 
    PRIVATE 
        -DSAMPLEAPI_EXPORTS 
        FOO=1
    PUBLIC 
        BAR=2
)

# 调用函数获取宏定义
get_target_all_definitions(MyLib RESULT_DEFS)

# 打印结果
message("所有宏定义：${RESULT_DEFS}")
# 输出示例：SAMPLEAPI_EXPORTS;FOO=1;BAR=2
```

### 功能特点

1. **显式参数传递**  
   通过第二个参数 `OUTPUT_VAR` 指定结果变量名，避免硬编码变量名

2. **健壮性增强**  
   - 添加目标存在性检查
   - 处理 `get_target_property` 返回的 `NOTFOUND` 情况
   - 支持带空格的编译选项（如 `-DFOO="bar baz"`）

3. **多来源合并**  
   涵盖以下来源的宏定义：
   - `target_compile_definitions` 的直接定义
   - `COMPILE_OPTIONS` 中的 `-D` 参数
   - 目录级 `COMPILE_DEFINITIONS`
   - 全局编译标志（如 `CMAKE_CXX_FLAGS`）
   - 依赖项的 `INTERFACE_COMPILE_DEFINITIONS`

4. **去重处理**  
   使用 `list(REMOVE_DUPLICATES)` 确保结果唯一性

### 注意事项

1. **生成器表达式限制**  
   若定义包含生成器表达式（如 `$<CONFIG:Debug>`），需要 CMake 3.19+ 的 `cmake_language` 命令展开。可在函数内添加以下代码段处理：

```cmake
# 在阶段1后添加生成器表达式处理
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
    cmake_language(EVAL CODE "
        string(APPEND GENEX_RESULT \"$<JOIN:$<TARGET_PROPERTY:${TARGET},COMPILE_DEFINITIONS>,;>\")
    ")
    list(APPEND ALL_DEFS ${GENEX_RESULT})
endif()
```

2. **作用域区分**  
   当前版本会合并所有作用域（PRIVATE/PUBLIC/INTERFACE）的定义，如需区分可见性，需要额外处理 `COMPILE_DEFINITIONS` 的 `$<BUILD_INTERFACE>` 生成器表达式

3. **性能优化**  
   对大型项目建议缓存结果：

```cmake
if(NOT DEFINED CACHE_ALL_DEFS_${TARGET})
    get_target_all_definitions(${TARGET} CACHE_ALL_DEFS_${TARGET})
endif()
set(${OUTPUT_VAR} ${CACHE_ALL_DEFS_${TARGET}} PARENT_SCOPE)
```