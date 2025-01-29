set(BoostVersion boost_1_87_0)
set(ImportedLibName ${BoostVersion}_partial)
set(v_ImportedLibRootDirPath ${c_RootThirdPartyDirPath}/boost/${BoostVersion})
set(v_UnzippedDirPath ${v_ImportedLibRootDirPath}/${ImportedLibName})
set(v_ZipFileName ${ImportedLibName}.zip)
set(v_SrcAddrZipFilePath ${c_StorageAddrPath}/ThirdParty/boost/${c_ProjectPlatform}/${v_ZipFileName})

include(${c_RootCMakeProjectFrameworkDirPath}/InlineDownloadAndUnzip.cmake)

# 设置 Boost 的安装路径
set(BOOST_ROOT "${v_UnzippedDirPath}")  # 替换成你的 Boost 安装路径
#set(BOOST_ROOT "I:/F/Fts/Proj/Test/Wishing/ThirdParty/boost/boost_1_73_0/boost_1_73_0_partial")

#set(Boost_USE_STATIC_LIBS OFF) # 测试用的构建版本为动态库, 因此须指定该标志 OFF

# 查找 Boost 库
find_package(Boost 1.87 REQUIRED COMPONENTS 
	chrono 
	#filesystem
)

# 链接 Boost 库
if(Boost_FOUND)
    target_link_libraries(${ModuleName} 
		PRIVATE Boost::chrono 
		#PRIVATE Boost::filesystem
	)
else()
	message(FATAL_ERROR "Failed to linking boost")
endif()

#begin, Required
unset(v_ImportedLibRootDirPath)
unset(v_ZipFileName)
unset(v_SrcAddrZipFilePath)
unset(v_UnzippedDirPath)
#end