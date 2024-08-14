
add_library(libclang SHARED IMPORTED)

target_include_directories(${TargetName} 
	PRIVATE "${RootThirdPartyPath}/include/llvm-project/clang/include"
)

target_link_libraries(${TargetName} PRIVATE libclang)

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	set(LibPath "${RootThirdPartyPath}/libclang/llvm-project/build/Windows/x64")
	set(LibPathDebug "${LibPath}/Debug/lib")
	set(LibPathRelease "${LibPath}/Release/lib")
	
	target_include_directories(${TargetName} 
		PRIVATE "${RootThirdPartyPath}/libclang/llvm-project/build/Windows/x64/include"
	)

	target_link_directories(${TargetName} PRIVATE 
		$<$<CONFIG:Debug>:${LibPathDebug}>
		$<$<CONFIG:Release>:${LibPathRelease}>
	)
else()
	message(ERROR "asdf")
endif()
