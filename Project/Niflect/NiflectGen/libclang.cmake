
add_library(libclang2 SHARED IMPORTED)

target_include_directories(${ModuleName} PRIVATE "${RootThirdPartyPath}/libclang/llvm-project/clang/include")

if(UNIX)
	message(STATUS "Target Is on UNIX")
	set(OsType Linux)
	set(DlPost .so)
	set(SlPost .a)
elseif(APPLE)
	message(STATUS "Target Is on APPLE")
	message(FATAL_ERROR "OsType & DynamicLibraryPrefix & DynamicLibraryPostfix are not specified")
elseif(WIN32)
	message(STATUS "Target Is on WIN32")
	set(OsType Windows)
	set(DlPost .dll)
	set(SlPost .lib)
endif()

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	set(LibPath "${RootThirdPartyPath}/libclang/llvm-project/build/${OsType}/x64")
	
	set(LIBCLANG_DLL_DEBUG "${LibPath}/Debug/bin/libclang${DlPost}")
	set(LIBCLANG_LIB_DEBUG "${LibPath}/Debug/lib/libclang${SlPost}")
	set(LIBCLANG_DLL_RELEASE "${LibPath}/Release/bin/libclang${DlPost}")
	set(LIBCLANG_LIB_RELEASE "${LibPath}/Release/lib/libclang${SlPost}")
	
	set_target_properties(libclang2 PROPERTIES
		IMPORTED_LOCATION_DEBUG "${LIBCLANG_DLL_DEBUG}"
		IMPORTED_LOCATION_RELEASE "${LIBCLANG_DLL_RELEASE}"
		IMPORTED_LOCATION_RELWITHDEBINFO "${LIBCLANG_DLL_DEBUG}"
		IMPORTED_LOCATION_MINSIZEREL "${LIBCLANG_DLL_RELEASE}"
	)
	
	if(WIN32)
		set_target_properties(libclang2 PROPERTIES
			IMPORTED_IMPLIB_DEBUG "${LIBCLANG_LIB_DEBUG}"
			IMPORTED_IMPLIB_RELEASE "${LIBCLANG_LIB_RELEASE}"
			IMPORTED_IMPLIB_RELWITHDEBINFO "${LIBCLANG_LIB_DEBUG}"
			IMPORTED_IMPLIB_MINSIZEREL "${LIBCLANG_LIB_RELEASE}"
		)
	endif()
	
	target_link_libraries(${ModuleName} PRIVATE libclang2)
	target_include_directories(${ModuleName} PRIVATE "${LibPath}/include")
else()
	message(ERROR "asdf")
endif()
