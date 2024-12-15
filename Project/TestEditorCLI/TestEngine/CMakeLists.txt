cmake_minimum_required(VERSION 3.20.0)

set(ModuleName TestEngine)

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

get_filename_component(NiflectGeneratedRootPath "${RootSourcePath}/../Generated/NiflectGenerated" ABSOLUTE)
set(ModuleGenPath ${NiflectGeneratedRootPath}/${ModuleName}/_GenSource)
set(GenIncludePath ${ModuleGenPath}/include)
#beign, 用于模式 EGeneratingHeaderAndSourceFileMode::ESourceAndHeader, 将生成文件加到模块
#file(GLOB_RECURSE GeneratedSrc ${ModuleGenPath}/*.cpp ${ModuleGenPath}/*.h)
#create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#list(APPEND SrcAll ${GeneratedSrc})
#end

add_library(${ModuleName} SHARED ${SrcAll})

target_precompile_headers(${ModuleName} PRIVATE ${SourcePath}/EngineDevelopmentMacro.h)

set_target_properties(${ModuleName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
)

target_include_directories(${ModuleName}
	PRIVATE ${SourcePath}
	PUBLIC ${IncludePath}
)

target_include_directories(${ModuleName}
	PRIVATE ${ModuleGenPath}
	PUBLIC ${GenIncludePath}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DENGINE_EXPORTS
	PRIVATE -DENGINE_C_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)
target_link_libraries(${ModuleName} PRIVATE TestModule1)

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

set(NiflectGeneratedModulePrivateH ${ModuleGenPath}/${ModuleName}_private.h)
add_custom_command(
    OUTPUT "${NiflectGeneratedModulePrivateH}"
    COMMAND "${RootSourcePath}/../Build/NiflectGenTool/${ToolRelPathForTest}/Debug/NiflectGenTool/NiflectGenTool${ExeExt}" 
            -n ${ModuleName} 
            ${ArgsModuleInclude}
            -am ENGINE_API 
            -amh "${IncludePath}/Engine/EngineCommon.h" 
            -a "${IncludePath}/EngineAccessorSetting.h" 
            -t "${RootSourcePath}/Niflect/include" 
            -I "${IncludePath}" 
            -I "${RootSourcePath}/TestModule1/include" 
            -g "${NiflectGeneratedRootPath}"
			-gbt 
    DEPENDS ${ModuleInclude}
    COMMENT "NiflectGenTool generating ..."
)

add_custom_target(NiflectGenTool_${ModuleName} DEPENDS "${NiflectGeneratedModulePrivateH}")
set_target_properties(NiflectGenTool_${ModuleName} PROPERTIES FOLDER "AutoGen")
add_dependencies(${ModuleName} NiflectGenTool_${ModuleName})

include(../TestModule1/TestModule1.cmake)
