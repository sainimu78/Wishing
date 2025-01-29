cmake_minimum_required(VERSION 3.10.0)

include(../InitSampleRootPath.cmake)

set(c_ProjectName SampleProject_Qt_5_8_0)

set(c_SampleRootSourceDirPath ${c_RootSourceDirPath}/Sample/${c_ProjectName})

include(${c_RootCMakeProjectFrameworkDirPath}/ProjectBegin.cmake)
project(${c_ProjectName})
include(${c_RootCMakeProjectFrameworkDirPath}/ProjectEnd.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Editor)
endif()

add_subdirectory(Editor)
add_subdirectory(Engine)

include(${c_RootCMakeProjectFrameworkDirPath}/Release.cmake)
include(${c_RootCMakeProjectFrameworkDirPath}/Cleanup.cmake)