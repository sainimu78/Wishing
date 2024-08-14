
#message(STATUS "AAAAAAAAAAAAAAAAA  ${CMAKE_CXX_COMPILER}")

# CMAKE_CXX_COMPILER 略特殊, 默认无设置时, 需要在 project 命令后执行才具有检测到的默认路径 Compiler 
if(CMAKE_CXX_COMPILER MATCHES "c\\+\\+$")
	message(STATUS "Compiler Is Using GCC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-zero-length")
elseif(CMAKE_CXX_COMPILER MATCHES "clang\\+\\+$")
	message(STATUS "Compiler Is Using Clang")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-zero-length")
elseif(MSVC)
	message(STATUS "Compiler Is Using MSVC")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

if(UNIX)
	message(STATUS "Target Is on UNIX")
elseif(APPLE)
	message(STATUS "Target Is on APPLE")
elseif(WIN32)
	message(STATUS "Target Is on WIN32")
endif()