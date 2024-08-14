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
#target_link_libraries(${ModuleName} PRIVATE libclang)

#add_subdirectory(libclang)

add_library(libclang2 SHARED IMPORTED)

target_include_directories(${ModuleName} PRIVATE "${RootThirdPartyPath}/libclang/llvm-project/clang/include")

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	set(LibPath "${RootThirdPartyPath}/libclang/llvm-project/build/Windows/x64")
	
	set(LIBCLANG_DLL_DEBUG "${LibPath}/Debug/bin/libclang.dll")
	set(LIBCLANG_LIB_DEBUG "${LibPath}/Debug/lib/libclang.lib")
	set(LIBCLANG_DLL_RELEASE "${LibPath}/Release/bin/libclang.dll")
	set(LIBCLANG_LIB_RELEASE "${LibPath}/Release/lib/libclang.lib")
	
	set_target_properties(libclang2 PROPERTIES
		IMPORTED_LOCATION_DEBUG "${LIBCLANG_DLL}"
		IMPORTED_IMPLIB_DEBUG "${LIBCLANG_LIB_DEBUG}"
		IMPORTED_LOCATION_RELEASE "${LIBCLANG_DLL_RELEASE}"
		IMPORTED_IMPLIB_RELEASE "${LIBCLANG_LIB_RELEASE}"
		IMPORTED_LOCATION_RELWITHDEBINFO "${LIBCLANG_DLL_DEBUG}"
		IMPORTED_IMPLIB_RELWITHDEBINFO "${LIBCLANG_LIB_DEBUG}"
		IMPORTED_LOCATION_MINSIZEREL "${LIBCLANG_DLL_RELEASE}"
		IMPORTED_IMPLIB_MINSIZEREL "${LIBCLANG_LIB_RELEASE}"
	)
	
	target_link_libraries(${ModuleName} PRIVATE libclang2)
	target_include_directories(${ModuleName} PRIVATE "${LibPath}/include")
else()
	message(ERROR "asdf")
endif()
