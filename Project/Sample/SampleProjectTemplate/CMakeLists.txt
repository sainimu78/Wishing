cmake_minimum_required(VERSION 3.20.0)

include(../InitSampleRootPath.cmake)

set(c_ProjectName SampleProjectTemplate)

set(c_SampleRootSourceDirPath ${c_RootSourceDirPath}/Sample/${c_ProjectName})

include(${c_RootCMakeDirPath}/ProjectBegin.cmake)
project(${c_ProjectName})
include(${c_RootCMakeDirPath}/ProjectEnd.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT SampleApp)
endif()

add_subdirectory(SampleApp)
add_subdirectory(SampleAPI)

include(${c_RootCMakeDirPath}/Release.cmake)
include(${c_RootCMakeDirPath}/Cleanup.cmake)