set(v_ImportedLibName Niflect)
set(v_ImportedLibRootDirPath ${c_RootThirdPartyDirPath}/${v_ImportedLibName})
set(v_UnzippedDirPath ${v_ImportedLibRootDirPath}/${v_ImportedLibName})
set(v_ZipFileName ${v_ImportedLibName}.zip)
set(v_SrcAddrZipFilePath ${c_StorageAddrPath}/Release/${c_ProjectPlatform}/${v_ZipFileName})
set(v_LibPlatformArchDirPath ${v_UnzippedDirPath}/build/${c_ProjectPlatform}/${c_ProjectArch})
set(v_LibIncludeDirPath ${v_UnzippedDirPath}/include)

include(${c_RootCMakeDirPath}/ImportShared.cmake)