cmake_minimum_required(VERSION 3.20.0)

include(../SampleRootPathSetup.cmake)
set(ProjectName AssetCreator)
set(ProjectRootSourcePath "${RootSourcePath}/Sample/${ProjectName}")
set(ProjectGeneratedRootPath "${GeneratedRootPath}/Sample/${ProjectName}")

include(${RootProjectPath}/CommonBeforeProject.cmake)
project(${ProjectName})
include(${RootProjectPath}/CommonAfterProject.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Editor)
endif()

add_subdirectory(Editor)
add_subdirectory(Engine)
include(${RootProjectPath}/Niflect/Niflect.cmake)