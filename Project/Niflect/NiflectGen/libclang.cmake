
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