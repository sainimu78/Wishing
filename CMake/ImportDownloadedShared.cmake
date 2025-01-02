set(DstDownloadedFilePath ${v_ImportedLibRootDirPath}/${v_ZipFileName})
if(PROJECT_SETUP OR NOT EXISTS "${v_UnzippedDirPath}")
	download_zip_replace_dir_if_not_exists(${v_SrcAddrZipFilePath} ${DstDownloadedFilePath} ${v_UnzippedDirPath} IsDownloaded)
	if(IsDownloaded)
		file(COPY "${v_LibPlatformArchDirPath}/" DESTINATION "${c_ProjectPlatformArchDirPath}/")
	endif()
endif()

target_include_directories(${ModuleName} PRIVATE "${v_ListLibIncludeDirPath}")

if(v_ListImportedLibFilePathDebug)
	target_link_libraries(${ModuleName} PRIVATE "$<$<CONFIG:Debug>:${v_ListImportedLibFilePathDebug}>")
endif()
if(v_ListImportedLibFilePathRelease)
	target_link_libraries(${ModuleName} PRIVATE "$<$<CONFIG:Release>:${v_ListImportedLibFilePathRelease}>")
endif()

set(v_ListLibFileName ${v_ListImportedLibFileName})
set(v_LibDirPathDebug ${v_LibPlatformArchDirPath}/Debug/${c_LibDirName})
set(v_LibDirPathRelease ${v_LibPlatformArchDirPath}/Release/${c_LibDirName})
include(${c_RootCMakeDirPath}/InlinedLinkLibraries.cmake)

if(WIN32)
	set(BinDirPathDebug ${v_LibPlatformArchDirPath}/Debug/${c_BinDirName})
	set(BinDirPathRelease ${v_LibPlatformArchDirPath}/Release/${c_BinDirName})
	install(DIRECTORY "${BinDirPathDebug}/"
		DESTINATION "${c_ProjectInstallingTargetDirPathDebug}/${c_BinDirName}/"
		CONFIGURATIONS Debug
		#FILES_MATCHING PATTERN "*.so"
		USE_SOURCE_PERMISSIONS
	)
	install(DIRECTORY "${BinDirPathRelease}/"
		DESTINATION "${c_ProjectInstallingTargetDirPathRelease}/${c_BinDirName}/"
		CONFIGURATIONS Release
		#FILES_MATCHING PATTERN "*.so"
		USE_SOURCE_PERMISSIONS
	)
else()
	install(DIRECTORY "${LibDirPathDebug}/"
		DESTINATION "${c_ProjectInstallingTargetDirPathDebug}/${c_LibDirName}/"
		CONFIGURATIONS Debug
		#FILES_MATCHING PATTERN "*.so"
		USE_SOURCE_PERMISSIONS
	)
	install(DIRECTORY "${LibDirPathRelease}/"
		DESTINATION "${c_ProjectInstallingTargetDirPathRelease}/${c_LibDirName}/"
		CONFIGURATIONS Release
		#FILES_MATCHING PATTERN "*.so"
		USE_SOURCE_PERMISSIONS
	)
endif()

#begin, Required
set(v_ImportedLibName "")
set(v_ImportedLibRootDirPath "")
set(v_UnzippedDirPath "")
set(v_ZipFileName "")
set(v_SrcAddrZipFilePath "")
set(v_LibPlatformArchDirPath "")
set(v_ListLibIncludeDirPath "")
set(v_LibPlatformArchIncludeDirPath "")
#end

#begin, Optional
set(v_DebugLibFileNamePostfix "")
set(v_ListImportedLibFilePathDebug "")
set(v_ListImportedLibFilePathRelease "")
set(v_ListImportedLibFileName "")
#end