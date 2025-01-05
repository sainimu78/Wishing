set(QtVersion Qt_5_8_0)
set(v_ImportedLibName ${QtVersion}_msvc2015_64)
set(v_ImportedLibRootDirPath ${c_RootThirdPartyDirPath}/Qt/${QtVersion})
set(v_UnzippedDirPath ${v_ImportedLibRootDirPath}/${v_ImportedLibName})
set(v_ZipFileName ${v_ImportedLibName}.zip)
set(v_SrcAddrZipFilePath ${c_StorageAddrPath}/ThirdParty/Qt/${c_ProjectPlatform}/${v_ZipFileName})
set(v_LibPlatformArchDirPath ${v_UnzippedDirPath}/build/${c_ProjectPlatform}/${c_ProjectArch})
set(v_DebugLibFileNamePostfix d)

include(${c_RootThirdPartyDirPath}/Qt/Qt_5_x/Deps.cmake)

set(QtIncludeRootDirPath ${v_UnzippedDirPath}/include)
list(APPEND v_ListLibIncludeDirPathPrivate ${QtIncludeRootDirPath})
foreach(It ${QtIncludeDirNames})
    list(APPEND v_ListLibIncludeDirPathPrivate ${QtIncludeRootDirPath}/${It})
endforeach()
foreach(It ${QtLibFileNames})
	list(APPEND v_ListImportedLibFileName ${It})
endforeach()

include(${c_RootCMakeDirPath}/ImportLibDownloaded.cmake)