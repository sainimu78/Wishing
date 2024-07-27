cmake_minimum_required(VERSION 3.10.0)

include(CMake/Common.cmake)

project(Interedit)

set(AppOutputPath "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}")
set(ProjectSourcePath "${CMAKE_CURRENT_SOURCE_DIR}")
#set(EngineSourcePath "${ProjectSourcePath}/../Engine")
#set(DependenciesPath "${EngineSourcePath}/Dependencies")
#set(S3EngineIncludePath "${EngineSourcePath}/S3Engine")
#set(BaseSourcePath "${EngineSourcePath}/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${AppOutputPath}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${AppOutputPath}/Release)

add_subdirectory(Editor)
add_subdirectory(Engine)