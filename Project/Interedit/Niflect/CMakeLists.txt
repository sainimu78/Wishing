cmake_minimum_required(VERSION 3.10.0)

set(ModuleName Niflect)

set(SourcePath ${RootSourcePath}/Niflect)

file(GLOB_RECURSE SrcAll ${SourcePath}/*.cpp ${SourcePath}/*.h)
#list(APPEND SrcAll ${SrcDefault})
#todo: 现代码未合并到引擎, 因此暂使用SampleTest的路径, 合并后相应调整, 该cpp为测试内存管理复用性, 使用该cpp后即可使用TSharedPtr这类模板, 总之为测试目的, 实际上可不使用
#添加到工程中将看到2层名为".."的目录, 属正常, 这是由于NiflectGen的工程未与其它工程通过engine_ref的CMakeLists.txt调用, 因此ProjectSourcePath带有"..", 如有必要, 加入到engine_ref的CMakeLists.txt即可
#list(APPEND SrcAll ${BaseSourcePath}/Niflect/Memory/Default/DefaultMemory.cpp)

create_source_group(${RootSourcePath} ${SrcAll})

add_library(${ModuleName} SHARED ${SrcAll})
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

if(CMAKE_CXX_COMPILER MATCHES "c\\+\\+")
	message(STATUS "Using GCC")
	find_library(PTHREAD_LIB pthread)
	if (PTHREAD_LIB)
		target_link_libraries(${ModuleName} PRIVATE ${PTHREAD_LIB})
	endif()
elseif(CMAKE_CXX_COMPILER MATCHES "clang\\+\\+")
	message(STATUS "Using Clang")
	
elseif(MSVC)
	message(STATUS "Using MSVC")
	
endif()

target_compile_definitions(${ModuleName} 
	PRIVATE -DNIFLECT_EXPORTS
)

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
