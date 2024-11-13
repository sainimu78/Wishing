
#add_library(libclang2 STATIC IMPORTED)

target_include_directories(${ModuleName} PRIVATE "${RootThirdPartyPath}/libclang/llvm-project/clang/include")

target_compile_definitions(${ModuleName} PUBLIC CINDEX_NO_EXPORTS)

include(libclangStaticDeps.cmake)

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
	set(MyArch x64)
else()
	message(ERROR "asdf")
endif()

set(LibPath "${RootThirdPartyPath}/libclang/llvm-project/build/${OsType}/${MyArch}")
	
set(DebugLibPathList)
set(ReleaseLibPathList)
foreach(libName ${MyLibNames})
    list(APPEND DebugLibPathList "${LibPath}/Debug/lib/${libName}${SlPost}")
endforeach()
foreach(libName ${MyLibNames})
    list(APPEND ReleaseLibPathList "${LibPath}/Release/lib/${libName}${SlPost}")
endforeach()

if(WIN32)
	target_include_directories(${ModuleName} PRIVATE "${LibPath}/include")
	list(APPEND DebugLibPathList Version${SlPost})
	list(APPEND ReleaseLibPathList Version${SlPost})
endif()

target_link_libraries(${ModuleName} PRIVATE 
	$<$<CONFIG:Debug>:${DebugLibPathList}>
	$<$<CONFIG:Release>:${ReleaseLibPathList}>
)