target_include_directories(${ModuleName} PRIVATE "${v_ListLibIncludeDirPath}")

if(v_ListImportedLibFilePathDebug)
	target_link_libraries(${ModuleName} PRIVATE "$<$<CONFIG:Debug>:${v_ListImportedLibFilePathDebug}>")
endif()
if(v_ListImportedLibFilePathRelease)
	target_link_libraries(${ModuleName} PRIVATE "$<$<CONFIG:Release>:${v_ListImportedLibFilePathRelease}>")
endif()

set(v_ListLibFileName ${v_ListImportedLibFileName})
set(v_LibDirPathDebug ${v_InstalledLibDirPathDebug})
set(v_LibDirPathRelease ${v_InstalledLibDirPathRelease})
if(NOT v_LibDirPathDebug)
	set(v_LibDirPathDebug ${v_LibPlatformArchDirPath}/Debug/${c_LibDirName})
endif()
if(NOT v_LibDirPathRelease)
	set(v_LibDirPathRelease ${v_LibPlatformArchDirPath}/Release/${c_LibDirName})
endif()
include(${c_RootCMakeDirPath}/InlinedLinkLibraries.cmake)

#begin, Required
set(v_ListLibIncludeDirPath "")
#end

#begin, Optional
set(v_LibPlatformArchDirPath "")
set(v_DebugLibFileNamePostfix "")
set(v_ListImportedLibFilePathDebug "")
set(v_ListImportedLibFilePathRelease "")
set(v_ListImportedLibFileName "")
set(v_InstalledLibDirPathDebug "")
set(v_InstalledLibDirPathRelease "")
#end