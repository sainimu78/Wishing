## 问题

/permissive- /MP /ifcOutput "Core.dir\Debug\" /we"4002" /we"4003" /GS /Zc:rvalueCast /W4 /wd"4201" /wd"4251" /wd"4324" /wd"4345" /wd"4100" /wd"4189" /wd"4127" /wd"4245" /wd"4389" /wd"4310" /wd"4714" /wd"6326" /wd"5240" /Zc:wchar_t /I"F:\Fts\Proj\Test\ezEngine\Code\Engine" /I"F:\Fts\Proj\Test\ezEngine\Code\ThirdParty" /Zi /Gm- /Od /Ob1 /Fd"Core.dir\Debug\vc143.pdb" /Zc:inline /fp:precise /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /D "WIN32" /D "_WINDOWS" /D "BUILDSYSTEM_COMPILE_ENGINE_AS_DLL" /D "BUILDSYSTEM_SDKVERSION_MAJOR=23" /D "BUILDSYSTEM_SDKVERSION_MINOR=12" /D "BUILDSYSTEM_SDKVERSION_PATCH=0" /D "BUILDSYSTEM_BUILDTYPE=\"Debug\"" /D "BUILDSYSTEM_BUILDTYPE_Debug" /D "BUILDSYSTEM_BUILDING_CORE_LIB" /D "BUILDSYSTEM_ENABLE_ENET_SUPPORT" /D "BUILDSYSTEM_ENABLE_ZSTD_SUPPORT" /D "ZSTD_DLL_IMPORT=1" /D "BUILDSYSTEM_ENABLE_ZLIB_SUPPORT" /D "ZLIB_DLL=1" /D "BUILDSYSTEM_HAS_TEXTURE" /D "BUILDSYSTEM_ENABLE_LUA_SUPPORT" /D "BUILDSYSTEM_ENABLE_DUKTAPE_SUPPORT" /D "CMAKE_INTDIR=\"Debug\"" /D "Core_EXPORTS" /errorReport:prompt /WX /Zc:forScope /RTC1 /GR- /Gd /MDd /std:c++17 /Fa"Core.dir\Debug\" /EHsc /nologo /Fo"Core.dir\Debug\" /Fp"Core.dir\Debug\ezCore.pch" /diagnostics:column 
这是一份VS项目的Debug配置编译器命令参数

/permissive- /MP /ifcOutput "Core.dir\Dev\" /we"4002" /we"4003" /GS /Zc:rvalueCast /W4 /wd"4201" /wd"4251" /wd"4324" /wd"4345" /wd"4100" /wd"4189" /wd"4127" /wd"4245" /wd"4389" /wd"4310" /wd"4714" /wd"6326" /wd"5240" /Zc:wchar_t /I"F:\Fts\Proj\Test\ezEngine\Code\Engine" /I"F:\Fts\Proj\Test\ezEngine\Code\ThirdParty" /Zi /Gm- /O2 /Ob1 /Fd"Core.dir\Dev\vc143.pdb" /Zc:inline /fp:precise /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "BUILDSYSTEM_COMPILE_ENGINE_AS_DLL" /D "BUILDSYSTEM_SDKVERSION_MAJOR=23" /D "BUILDSYSTEM_SDKVERSION_MINOR=12" /D "BUILDSYSTEM_SDKVERSION_PATCH=0" /D "BUILDSYSTEM_BUILDTYPE=\"Dev\"" /D "BUILDSYSTEM_BUILDTYPE_Dev" /D "BUILDSYSTEM_BUILDING_CORE_LIB" /D "BUILDSYSTEM_ENABLE_ENET_SUPPORT" /D "BUILDSYSTEM_ENABLE_ZSTD_SUPPORT" /D "ZSTD_DLL_IMPORT=1" /D "BUILDSYSTEM_ENABLE_ZLIB_SUPPORT" /D "ZLIB_DLL=1" /D "BUILDSYSTEM_HAS_TEXTURE" /D "BUILDSYSTEM_ENABLE_LUA_SUPPORT" /D "BUILDSYSTEM_ENABLE_DUKTAPE_SUPPORT" /D "CMAKE_INTDIR=\"Dev\"" /D "Core_EXPORTS" /errorReport:prompt /WX /Zc:forScope /GR- /Gd /MD /std:c++17 /Fa"Core.dir\Dev\" /EHsc /nologo /Fo"Core.dir\Dev\" /Fp"Core.dir\Dev\ezCore.pch" /diagnostics:column 
这是一份VS项目的Dev配置编译器命令参数

/permissive- /MP /ifcOutput "Core.dir\Shipping\" /we"4002" /we"4003" /GS /Zc:rvalueCast /W4 /wd"4201" /wd"4251" /wd"4324" /wd"4345" /wd"4100" /wd"4189" /wd"4127" /wd"4245" /wd"4389" /wd"4310" /wd"4714" /wd"6326" /wd"5240" /Zc:wchar_t /I"F:\Fts\Proj\Test\ezEngine\Code\Engine" /I"F:\Fts\Proj\Test\ezEngine\Code\ThirdParty" /Gm- /Ox /Ob2 /Fd"Core.dir\Shipping\vc143.pdb" /Zc:inline /fp:precise /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "BUILDSYSTEM_COMPILE_ENGINE_AS_DLL" /D "BUILDSYSTEM_SDKVERSION_MAJOR=23" /D "BUILDSYSTEM_SDKVERSION_MINOR=12" /D "BUILDSYSTEM_SDKVERSION_PATCH=0" /D "BUILDSYSTEM_BUILDTYPE=\"Shipping\"" /D "BUILDSYSTEM_BUILDTYPE_Shipping" /D "BUILDSYSTEM_BUILDING_CORE_LIB" /D "BUILDSYSTEM_ENABLE_ENET_SUPPORT" /D "BUILDSYSTEM_ENABLE_ZSTD_SUPPORT" /D "ZSTD_DLL_IMPORT=1" /D "BUILDSYSTEM_ENABLE_ZLIB_SUPPORT" /D "ZLIB_DLL=1" /D "BUILDSYSTEM_HAS_TEXTURE" /D "BUILDSYSTEM_ENABLE_LUA_SUPPORT" /D "BUILDSYSTEM_ENABLE_DUKTAPE_SUPPORT" /D "CMAKE_INTDIR=\"Shipping\"" /D "Core_EXPORTS" /errorReport:prompt /WX /Zc:forScope /GR- /Gd /Oi /MD /std:c++17 /Fa"Core.dir\Shipping\" /EHsc /nologo /Fo"Core.dir\Shipping\" /Fp"Core.dir\Shipping\ezCore.pch" /diagnostics:column 
这是一份VS项目的Shipping配置编译器命令参数

请说明三者配置的在调试体验上的区别

## GPT

性能测试是指功能运行时间消耗还是内存消耗, 我疑惑在于如果是为功能运行时间消耗的测试, 那不如使用Shipping模式更准确?

AI

你的疑问非常好。在性能测试中，确实有多个方面需要考虑，包括功能运行时间消耗和内存消耗。下面我们分别讨论一下这两个方面，并解释为什么在某些情况下使用开发（Dev）模式进行性能测试是有意义的。

### 1. 性能测试的定义

性能测试通常包括：

- **响应时间**：功能执行所需的时间。
- **吞吐量**：在特定时间内处理的请求数量。
- **资源消耗**：包括内存使用、CPU占用、磁盘I/O和网络带宽等。

### 2. Shipping模式的优缺点

- 优势

  ：

  - Shipping模式在编译时进行了最高级别的优化，因此它能够提供更好的运行时性能，接近于最终用户可能体验到的产品性能。

- 劣势

  ：

  - 由于优化，某些代码可能会被优化掉，这意味着调试困难，并且在某些情况下，可能会影响到某些性能瓶颈的分析。
  - 在Shipping模式中，未启用调试信息，导致在性能测试时追踪和分析问题变得更加困难。

### 3. Dev模式的优缺点

- 优势

  ：

  - Dev模式提供了一定程度的优化，同时保留了调试信息。这种平衡使得你可以在进行性能测试的同时，快速定位和识别问题。
  - 在Dev模式下，虽然进行了优化，但优化级别不如Shipping模式，因此某些性能瓶颈可能更容易被发现。

- 劣势

  ：

  - 由于不是最高级别的优化，可能无法完全反映最终版本的性能表现，尤其是在极端情况下。

### 4. 论关于选择的依据

- 在**初期开发阶段**，使用Dev模式进行性能测试可能更有利，因为它允许开发者在不牺牲太多性能的情况下，更容易识别性能问题。
- 在**接近发布阶段**的最终性能测试中，使用Shipping模式是合适的，这是因为此时重点在于了解最终用户所体验到的实际性能。

### 结论

因此，选择Dev模式或Shipping模式进行性能测试，应该根据测试的阶段和目标来决定。在开发早期，Dev模式提供了更好的调试体验和问题发现能力。而在发布前的最后检查中，Shipping模式将提供更接近实际用户体验的性能表现。