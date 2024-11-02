cmake_minimum_required(VERSION 3.20.0)

set(ModuleName Engine)

set(SourcePath ${RootSourcePath}/Engine)

file(GLOB_RECURSE ModuleSrc ${SourcePath}/*.cpp ${SourcePath}/*.h)
set(SrcAll "")
list(APPEND SrcAll ${ModuleSrc})

create_source_group(${RootSourcePath} ${SrcAll})

get_filename_component(NiflectGeneratedRootPath "${RootSourcePath}/../Generated/NiflectGenerated" ABSOLUTE)
set(GeneratedSrcPath ${NiflectGeneratedRootPath}/ModuleReg/${ModuleName})
file(GLOB_RECURSE GeneratedSrc ${GeneratedSrcPath}/*.cpp ${GeneratedSrcPath}/*.h)
create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#set_property(SOURCE ${GeneratedSrc} PROPERTY FOLDER "Hidden")
list(APPEND SrcAll ${GeneratedSrc})
set(GeneratedSrcPath ${NiflectGeneratedRootPath}/TypeReg/${ModuleName})
file(GLOB_RECURSE GeneratedSrc ${GeneratedSrcPath}/*.cpp ${GeneratedSrcPath}/*.h)
create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#set_property(SOURCE ${GeneratedSrc} PROPERTY FOLDER "Hidden")
list(APPEND SrcAll ${GeneratedSrc})

add_library(${ModuleName} SHARED ${SrcAll})

target_precompile_headers(${ModuleName} PRIVATE ${SourcePath}/EngineDevelopmentMacro.h)

#set_target_properties(${ModuleName} PROPERTIES LINKER_LANGUAGE CXX)
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
)
target_compile_definitions(${ModuleName}
	PRIVATE -DENGINE_EXPORTS
	PRIVATE -DENGINE_C_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)

set(LinkParentName ${ModuleName})
#set(ThirdPartyPath "ThirdParty")

#add_subdirectory(${ThirdPartyPath}/clang)
#target_include_directories(${LinkParentName} 
#	PRIVATE "${DependenciesPath}/include/llvm-project/clang/include"
#	PRIVATE "${DependenciesPath}/include/llvm-project/llvm/include"
#)
#target_link_libraries(${LinkParentName} PRIVATE libclang)

#target_include_directories(${LinkParentName}
#	PRIVATE "${ThirdPartyPath}/mustache_From_Picolo/include"
#)
