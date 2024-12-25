cmake_minimum_required(VERSION 3.20.0)

set(ModuleName TestEngine)

set(ModuleRootPath ${RootSourcePath}/${ModuleName})
set(ModuleSourcePath ${ModuleRootPath}/src)
set(ModuleIncludePath ${ModuleRootPath}/include)

set(ModuleIncludePaths "")
list(APPEND ModuleIncludePaths ${ModuleIncludePath})
list(APPEND ModuleIncludePaths ${RootSourcePath}/TestModule1/include)

file(GLOB_RECURSE ModuleSources ${ModuleSourcePath}/*.cpp ${ModuleSourcePath}/*.h)
create_source_group(${ModuleSourcePath} ${ModuleSources})
file(GLOB_RECURSE ModuleHeaders ${ModuleIncludePath}/*.h)
create_source_group(${ModuleIncludePath} ${ModuleHeaders})
set(SrcAll "")
list(APPEND SrcAll ${ModuleSources})
list(APPEND SrcAll ${ModuleHeaders})

set(GenOutputDirPath ${ProjectGeneratedRootPath}/${ModuleName})
set(GenSourcePrivate ${GenOutputDirPath}/_GenSource)
set(GenSourcePublic ${GenSourcePrivate}/include)
#beign, 用于模式 EGeneratingHeaderAndSourceFileMode::ESourceAndHeader, 将生成文件加到模块
#file(GLOB_RECURSE GeneratedSrc ${GenSourcePrivate}/*.cpp ${GenSourcePrivate}/*.h)
#create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#list(APPEND SrcAll ${GeneratedSrc})
#end

add_library(${ModuleName} SHARED ${SrcAll})

target_precompile_headers(${ModuleName} PRIVATE ${ModuleSourcePath}/EngineDevelopmentMacro.h)

set_target_properties(${ModuleName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
)

target_include_directories(${ModuleName}
	PRIVATE ${ModuleSourcePath}
	PUBLIC ${ModuleIncludePaths}
)

target_include_directories(${ModuleName}
	PRIVATE ${GenSourcePrivate}
	PUBLIC ${GenSourcePublic}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DENGINE_EXPORTS
	PRIVATE -DENGINE_C_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)
target_link_libraries(${ModuleName} PRIVATE TestModule1)

set(ArgsModuleHeaders "")
foreach(It IN LISTS ModuleHeaders)
    list(APPEND ArgsModuleHeaders "-h" "${It}")
endforeach()
set(ArgsModuleIncludePaths "")
foreach(It IN LISTS ModuleIncludePaths)
	list(APPEND ArgsModuleIncludePaths "-I" "${It}")
endforeach()

set(ToolRelPathForTest Linux/Make_x64)
set(ExeExt )
if (WIN32)
	set(ExeExt .exe)
	set(ToolRelPathForTest Windows/vs2022_x64)
endif()

set(NiflectGeneratedModulePrivateH ${GenSourcePrivate}/${ModuleName}_private.h)
add_custom_command(
    OUTPUT "${NiflectGeneratedModulePrivateH}"
    COMMAND "${RootSourcePath}/../Build/NiflectGenTool/${ToolRelPathForTest}/Debug/NiflectGenTool/NiflectGenTool${ExeExt}" 
            -n ${ModuleName} 
            ${ArgsModuleHeaders}
            -am ENGINE_API 
            -amh "${ModuleIncludePath}/Engine/EngineCommon.h" 
            -a "${ModuleIncludePath}/EngineAccessorSetting.h" 
            -t "${RootSourcePath}/Niflect/include" 
            ${ArgsModuleIncludePaths} 
            -g "${GenOutputDirPath}"
			-gbt 
    DEPENDS ${ModuleHeaders}
    COMMENT "NiflectGenTool ${ModuleName}"
)

add_custom_target(NiflectGenTool_${ModuleName} DEPENDS "${NiflectGeneratedModulePrivateH}")
set_target_properties(NiflectGenTool_${ModuleName} PROPERTIES FOLDER "AutoGen")
add_dependencies(${ModuleName} NiflectGenTool_${ModuleName})

#if(UNIX)
#	file(MAKE_DIRECTORY ${NiflectGeneratedRootPath}) # 由于创建目录的函数实现存在缺陷, NiflectGenTool 并发执行时出现首次创建不存在的输出目录失败与之后写文件失败, 因此仅在 UNIX 上通过 cmake 创建输出目录
#endif()

include(../TestModule1/TestModule1.cmake)
