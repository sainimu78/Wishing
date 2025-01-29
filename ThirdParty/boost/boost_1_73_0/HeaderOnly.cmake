set(BoostVersion boost_1_73_0)
set(ImportedLibName ${BoostVersion}_partial)
set(v_ImportedLibRootDirPath ${c_RootThirdPartyDirPath}/boost/${BoostVersion})
set(v_UnzippedDirPath ${v_ImportedLibRootDirPath}/${ImportedLibName})
set(v_ZipFileName ${ImportedLibName}.zip)
set(v_SrcAddrZipFilePath ${c_StorageAddrPath}/ThirdParty/boost/${v_ZipFileName})

list(APPEND v_ListLibIncludeDirPathPrivate ${v_UnzippedDirPath})

include(${c_RootCMakeProjectFrameworkDirPath}/ImportLibDownloaded.cmake)



#begin, 仅以头文件接入也可通过 find_package
#注: 默认 install 的目录结构 Windows 与 Ubuntu 是不同的, 因此使用 find_package 是有一定意义的
#find_package(Boost REQUIRED)
#add_executable(MyExecutable main.cpp)  # 请替换为你的源文件
#target_include_directories(MyExecutable PRIVATE ${Boost_INCLUDE_DIRS})
#end