cmake_minimum_required(VERSION 3.10.0)

include(../InitSampleRootPath.cmake)

set(c_ProjectName SampleProject_Qt_6_8_1)

set(c_SampleRootSourceDirPath ${c_RootSourceDirPath}/Sample/${c_ProjectName})

include(${c_RootCMakeProjectFrameworkDirPath}/ProjectBegin.cmake)
project(${c_ProjectName})
include(${c_RootCMakeProjectFrameworkDirPath}/ProjectEnd.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Editor)
endif()

add_subdirectory(Editor)
add_subdirectory(Engine)

include(${c_RootCMakeProjectFrameworkDirPath}/Release.cmake)
include(${c_RootCMakeProjectFrameworkDirPath}/Cleanup.cmake)