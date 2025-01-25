#if(WIN32)
#	# #include "boost/asio.hpp" requires
#	target_compile_definitions(${ModuleName} PRIVATE _WIN32_WINNT=0x0601)
#    #add_definitions(-D_WIN32_WINNT=0x0601)
#endif()
include(${c_RootThirdPartyDirPath}/boost/boost_1_73_0/Static.cmake)