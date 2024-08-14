cmake_minimum_required(VERSION 3.10.0)

set(ModuleName libclang)

add_library(${ModuleName} SHARED IMPORTED)

#target_include_directories(${ModuleName} INTERFACE "${RootThirdPartyPath}/include/llvm-project/clang/include")
#set_target_properties(${ModuleName} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${RootThirdPartyPath}/include/llvm-project/clang/include")

include_directories("${RootThirdPartyPath}/libclang/llvm-project/clang/include")

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	set(LibPath "${RootThirdPartyPath}/libclang/llvm-project/build/Windows/x64")
	set(LibPathDebug "${LibPath}/Debug/lib")
	set(LibPathRelease "${LibPath}/Release/lib")
	
	#target_include_directories(${ModuleName} INTERFACE "${RootThirdPartyPath}/libclang/llvm-project/build/Windows/x64/include")
	#set_target_properties(${ModuleName} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${RootThirdPartyPath}/libclang/llvm-project/build/Windows/x64/include")
	
	#target_link_directories(${ModuleName} INTERFACE $<$<CONFIG:Debug>:${LibPathDebug}> $<$<CONFIG:Release>:${LibPathRelease}>)
	
	set_target_properties(${ModuleName} PROPERTIES
		IMPORTED_LOCATION_DEBUG "${LibPath}/Debug/bin/libclang.dll"
		IMPORTED_IMPLIB_DEBUG "${LibPath}/Debug/lib/libclang.lib"
		IMPORTED_LOCATION_RELEASE "${LibPath}/Release/bin/libclang.dll"
		IMPORTED_IMPLIB_RELEASE "${LibPath}/Release/lib/libclang.lib"
	)
	include_directories("${LibPath}/include")
else()
	message(ERROR "asdf")
endif()
