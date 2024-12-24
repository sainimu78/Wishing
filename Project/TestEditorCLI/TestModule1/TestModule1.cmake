cmake_minimum_required(VERSION 3.20.0)

set(ModuleName TestModule1)

set(ModuleRootPath ${RootSourcePath}/${ModuleName})
set(SourcePath ${ModuleRootPath}/src)
set(IncludePath ${ModuleRootPath}/include)

file(GLOB_RECURSE ModuleSrc ${SourcePath}/*.cpp ${SourcePath}/*.h)
create_source_group(${SourcePath} ${ModuleSrc})
file(GLOB_RECURSE ModuleInclude ${IncludePath}/*.h)
create_source_group(${IncludePath} ${ModuleInclude})
set(SrcAll "")
list(APPEND SrcAll ${ModuleSrc})
list(APPEND SrcAll ${ModuleInclude})

set(GenSourcePrivate ${ProjectGeneratedRootPath}/${ModuleName}/_GenSource)
set(GenSourcePublic ${GenSourcePrivate}/include)
#beign, 用于模式 EGeneratingHeaderAndSourceFileMode::ESourceAndHeader, 将生成文件加到模块
#file(GLOB_RECURSE GeneratedSrc ${GenSourcePrivate}/*.cpp ${GenSourcePrivate}/*.h)
#create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#list(APPEND SrcAll ${GeneratedSrc})
#end

add_library(${ModuleName} SHARED ${SrcAll})

set_target_properties(${ModuleName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
)

target_include_directories(${ModuleName}
	PRIVATE ${SourcePath}
	PUBLIC ${IncludePath}
)

target_include_directories(${ModuleName}
	PRIVATE ${GenSourcePrivate}
	PUBLIC ${GenSourcePublic}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DTESTMODULE1_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)

set(ArgsModuleInclude "")
foreach(It IN LISTS ModuleInclude)
    list(APPEND ArgsModuleInclude "-h" "${It}")
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
            ${ArgsModuleInclude}
            -am TESTMODULE1_API 
            -amh "${IncludePath}/TestModule1Common.h" 
            -a "${RootSourcePath}/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h" 
            -t "${RootSourcePath}/Niflect/include" 
            -I "${IncludePath}" 
            -g "${ProjectGeneratedRootPath}/${ModuleName}"
    DEPENDS ${ModuleInclude}
    COMMENT "NiflectGenTool generating ..."
)

add_custom_target(NiflectGenTool_${ModuleName} DEPENDS "${NiflectGeneratedModulePrivateH}")
set_target_properties(NiflectGenTool_${ModuleName} PROPERTIES FOLDER "AutoGen")
add_dependencies(${ModuleName} NiflectGenTool_${ModuleName})

#if(UNIX)
#	file(MAKE_DIRECTORY ${NiflectGeneratedRootPath}) # 由于创建目录的函数实现存在缺陷, NiflectGenTool 并发执行时出现首次创建不存在的输出目录失败与之后写文件失败, 因此仅在 UNIX 上通过 cmake 创建输出目录
#endif()