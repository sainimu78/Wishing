
#message(STATUS "AAAAAAAAAAAAAAAAA  ${CMAKE_CXX_COMPILER}")

# CMAKE_CXX_COMPILER 略特殊, 默认无设置时, 需要在 project 命令后执行才具有检测到的默认路径 Compiler 
if(CMAKE_CXX_COMPILER MATCHES "c\\+\\+$")
	message(STATUS "Using GCC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-zero-length")
elseif(CMAKE_CXX_COMPILER MATCHES "clang\\+\\+$")
	message(STATUS "Using Clang")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-zero-length")
elseif(MSVC)
	message(STATUS "Using MSVC")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()
