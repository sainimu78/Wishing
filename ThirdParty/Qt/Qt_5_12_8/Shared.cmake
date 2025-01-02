set(QtRootDirPath /usr)
set(QtIncludeRootDirPath ${QtRootDirPath}/include/x86_64-linux-gnu/qt5)
list(APPEND v_ListLibIncludeDirPath ${QtIncludeRootDirPath})

include(${c_RootThirdPartyDirPath}/Qt/Qt_5_x/Deps.cmake)

foreach(It ${QtIncludeDirNames})
    list(APPEND v_ListLibIncludeDirPath ${QtIncludeRootDirPath}/${It})
endforeach()
foreach(It ${QtLibFileNames})
	list(APPEND v_ListImportedLibFileName ${It})
endforeach()
set(QtLibRootDirPath ${QtRootDirPath}/lib/x86_64-linux-gnu)
set(v_InstalledLibDirPathDebug ${QtLibRootDirPath})
set(v_InstalledLibDirPathRelease ${QtLibRootDirPath})

include(${c_RootCMakeDirPath}/ImportInstalledShared.cmake)


#add_library(Qt_5_12_8 SHARED IMPORTED)
#
#
##set_target_properties(Qt_5_8 PROPERTIES
##    CXX_STANDARD 11
##    CXX_STANDARD_REQUIRED YES
##)
#
#if(UNIX)
#	message(STATUS "Target Is on UNIX")
#	set(OsType Linux)
#	set(libPre lib)
#	set(DlPost .so)
#	set(SlPost .a)
#	if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
#		set(ArchType x64)
#		set(Toolset msvc2015_64)
#	else()
#		set(ArchType x86)
#		set(Toolset msvc2015_86)
#	endif()
#elseif(APPLE)
#	message(STATUS "Target Is on APPLE")
#	message(FATAL_ERROR "OsType & DynamicLibraryPrefix & DynamicLibraryPostfix are not specified")
#elseif(WIN32)
#	message(STATUS "Target Is on WIN32")
#	set(OsType Windows)
#	set(DlPost .dll)
#	set(SlPost .lib)
#	if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
#		set(ArchType x64)
#		set(Toolset msvc2015_64)
#	else()
#		set(ArchType x86)
#		set(Toolset msvc2015_86)
#	endif()
#endif()
#
#if(WIN32)
#	set(QtRootPath "${RootThirdPartyPath}/Qt/Qt_5_12_8/build/${OsType}/5.12.12/${ArchType}/5.12/${Toolset}")
#	set(QtIncRootPath ${QtRootPath}/include)
#	set(LibPath "${QtRootPath}/bin")
#else()
#	set(QtRootPath "/usr")
#	set(QtIncRootPath ${QtRootPath}/include/x86_64-linux-gnu/qt5)
#	set(LibPath "${QtRootPath}/lib/x86_64-linux-gnu")
#endif()
#
#include(${RootThirdPartyPath}/Qt/Qt_5_x/Deps.cmake)
#
#target_include_directories(${ModuleName} PRIVATE "${QtIncRootPath}")
#set(incPathList)
#foreach(dirName ${MyIncDirNames})
#    list(APPEND incPathList "${QtIncRootPath}/${dirName}")
#endforeach()
#target_include_directories(${ModuleName} PRIVATE "${incPathList}")
#
#set(binListDebug)
#set(binListRelease)
#if(WIN32)
#	foreach(libName ${MyLibNames})
#		list(APPEND binListDebug "${LibPath}/${libPre}${libName}d${SlPost}")
#		list(APPEND binListRelease "${LibPath}/${libPre}${libName}${SlPost}")
#	endforeach()
#else()
#	target_compile_options(${ModuleName} PRIVATE -fPIC)
#	foreach(libName ${MyLibNames})
#		list(APPEND binListDebug "${LibPath}/${libPre}${libName}${DlPost}")
#		list(APPEND binListRelease "${LibPath}/${libPre}${libName}${DlPost}")
#	endforeach()
#endif()
#
#target_link_libraries(${ModuleName} PRIVATE
#	$<$<CONFIG:Debug>:${binListDebug}>
#	$<$<CONFIG:Release>:${binListRelease}>
#)
