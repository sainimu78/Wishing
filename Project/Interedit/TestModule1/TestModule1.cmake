cmake_minimum_required(VERSION 3.20.0)

set(ModuleName TestModule1)

set(SourcePath ${RootSourcePath}/${ModuleName})

file(GLOB_RECURSE ModuleSrc ${SourcePath}/*.cpp ${SourcePath}/*.h)
set(SrcAll "")
list(APPEND SrcAll ${ModuleSrc})

create_source_group(${RootSourcePath} ${SrcAll})

get_filename_component(NiflectGeneratedRootPath "${RootSourcePath}/../Generated/NiflectGenerated" ABSOLUTE)
set(NiflectGenHPath ${NiflectGeneratedRootPath}/${ModuleName}/GenH)
#beign, 用于模式 EGeneratingHeaderAndSourceFileMode::ESourceAndHeader, 将生成文件加到模块
set(GeneratedSrcPath ${NiflectGeneratedRootPath}/${ModuleName}/ModuleReg)
file(GLOB_RECURSE GeneratedSrc ${GeneratedSrcPath}/*.cpp ${GeneratedSrcPath}/*.h)
create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#set_property(SOURCE ${GeneratedSrc} PROPERTY FOLDER "Hidden")
list(APPEND SrcAll ${GeneratedSrc})
set(GeneratedSrcPath ${NiflectGeneratedRootPath}/${ModuleName}/TypeReg)
file(GLOB_RECURSE GeneratedSrc ${GeneratedSrcPath}/*.cpp ${GeneratedSrcPath}/*.h)
create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#set_property(SOURCE ${GeneratedSrc} PROPERTY FOLDER "Hidden")
list(APPEND SrcAll ${GeneratedSrc})
set(GeneratedSrcPath ${NiflectGenHPath})
file(GLOB_RECURSE GeneratedSrc ${GeneratedSrcPath}/*.cpp ${GeneratedSrcPath}/*.h)
create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#set_property(SOURCE ${GeneratedSrc} PROPERTY FOLDER "Hidden")
list(APPEND SrcAll ${GeneratedSrc})
#end

add_library(${ModuleName} SHARED ${SrcAll})

set_target_properties(${ModuleName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
)

target_include_directories(${ModuleName}
	#PRIVATE ${RootSourcePath}
	#PRIVATE ${S3EngineIncludePath}
	##todo: 现代码未合并到引擎, 因此暂使用SampleTest的路径, 合并后可移除
	#PRIVATE ${BaseSourcePath}
	PUBLIC ${RootSourcePath}
)

target_include_directories(${ModuleName}
	PRIVATE ${NiflectGeneratedRootPath}
	PUBLIC ${NiflectGenHPath}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DTESTMODULE1_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)
