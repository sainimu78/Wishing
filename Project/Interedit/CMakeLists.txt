cmake_minimum_required(VERSION 3.10.0)

include(../Common.cmake)

project(Interedit)

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

set(AppOutputPath ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME})
#set(RootSourcePath ${CMAKE_CURRENT_SOURCE_DIR}/../../Source)
get_filename_component(RootSourcePath "${CMAKE_CURRENT_SOURCE_DIR}/../../Source" ABSOLUTE)

#set(EngineSourcePath "${RootSourcePath}/../Engine")
#set(DependenciesPath "${EngineSourcePath}/Dependencies")
#set(S3EngineIncludePath "${EngineSourcePath}/S3Engine")
#set(BaseSourcePath "${EngineSourcePath}/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${AppOutputPath}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${AppOutputPath}/Release)

add_subdirectory(Editor)
add_subdirectory(Engine)
add_subdirectory(Base)
add_subdirectory(TestModule0)