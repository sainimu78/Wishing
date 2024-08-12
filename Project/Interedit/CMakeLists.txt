cmake_minimum_required(VERSION 3.10.0)

include(Common.cmake)

project(Interedit)

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
add_subdirectory(Niflect)
add_subdirectory(TestModule0)