cmake_minimum_required(VERSION 3.20.0)

set(ModuleName Engine)

set(SourcePath ${RootSourcePath}/${ModuleName}/src)
set(IncludePath ${RootSourcePath}/${ModuleName}/include)

file(GLOB_RECURSE ModuleSrc ${SourcePath}/*.cpp ${SourcePath}/*.h)
file(GLOB_RECURSE ModuleInclude ${IncludePath}/*.h)
set(SrcAll "")
list(APPEND SrcAll ${ModuleSrc})
list(APPEND SrcAll ${ModuleInclude})
create_source_group(${RootSourcePath} ${SrcAll})

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

include(../TestModule1/TestModule1.cmake)
