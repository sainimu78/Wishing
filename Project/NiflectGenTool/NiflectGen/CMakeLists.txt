cmake_minimum_required(VERSION 3.10.0)

set(ModuleName NiflectGen)

set(SourcePath ${RootSourcePath}/NiflectGen)

file(GLOB_RECURSE SrcAll ${SourcePath}/*.cpp ${SourcePath}/*.h)
#list(APPEND SrcAll ${SrcDefault})
#todo: 现代码未合并到引擎, 因此暂使用SampleTest的路径, 合并后相应调整, 该cpp为测试内存管理复用性, 使用该cpp后即可使用TSharedPtr这类模板, 总之为测试目的, 实际上可不使用
#添加到工程中将看到2层名为".."的目录, 属正常, 这是由于NiflectGen的工程未与其它工程通过engine_ref的CMakeLists.txt调用, 因此ProjectSourcePath带有"..", 如有必要, 加入到engine_ref的CMakeLists.txt即可
#list(APPEND SrcAll ${BaseSourcePath}/Niflect/Memory/Default/DefaultMemory.cpp)

create_source_group(${RootSourcePath} ${SrcAll})

add_library(${ModuleName} SHARED ${SrcAll})

target_precompile_headers(${ModuleName} PRIVATE ${SourcePath}/NiflectGenDevelopmentMacro.h)

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

target_compile_definitions(${ModuleName}
	PRIVATE -DNIFLECTGEN_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)

include(libclang.cmake)
