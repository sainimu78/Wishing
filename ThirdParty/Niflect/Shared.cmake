set(v_ImportedLibName Niflect)
set(v_ImportedLibRootDirPath ${c_RootThirdPartyDirPath}/${v_ImportedLibName})
set(v_UnzippedDirPath ${v_ImportedLibRootDirPath}/${v_ImportedLibName})
set(v_ZipFileName ${v_ImportedLibName}.zip)
set(v_SrcAddrZipFilePath ${c_StorageAddrPath}/Release/${c_ProjectPlatform}/${v_ZipFileName})
set(v_LibPlatformArchDirPath ${v_UnzippedDirPath}/build/${c_ProjectPlatform}/${c_ProjectArch})
list(APPEND v_LibIncludeDirPaths ${v_UnzippedDirPath}/include)
list(APPEND v_ImportedLibFileNames ${v_ImportedLibName})

include(${c_RootCMakeDirPath}/ImportShared2.cmake)