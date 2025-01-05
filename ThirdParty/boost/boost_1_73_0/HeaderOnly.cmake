set(BoostVersion boost_1_73_0)
set(ImportedLibName ${BoostVersion}_partial)
set(v_ImportedLibRootDirPath ${c_RootThirdPartyDirPath}/boost/${BoostVersion})
set(v_UnzippedDirPath ${v_ImportedLibRootDirPath}/${ImportedLibName})
set(v_ZipFileName ${ImportedLibName}.zip)
set(v_SrcAddrZipFilePath ${c_StorageAddrPath}/ThirdParty/boost/${v_ZipFileName})

list(APPEND v_ListLibIncludeDirPathPrivate ${v_UnzippedDirPath})

include(${c_RootCMakeDirPath}/ImportLibDownloaded.cmake)