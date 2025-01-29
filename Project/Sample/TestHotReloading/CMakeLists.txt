cmake_minimum_required(VERSION 3.10.0)

include(../InitSampleRootPath.cmake)

set(c_ProjectName TestHotReloading)

set(c_SampleRootSourceDirPath ${c_RootSourceDirPath}/Sample/${c_ProjectName})

include(${c_RootCMakeProjectFrameworkDirPath}/ProjectBegin.cmake)
project(${c_ProjectName})
include(${c_RootCMakeProjectFrameworkDirPath}/ProjectEnd.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT MyProject)
endif()

add_subdirectory(MyProject)

include(${c_RootCMakeProjectFrameworkDirPath}/Release.cmake)
include(${c_RootCMakeProjectFrameworkDirPath}/Cleanup.cmake)