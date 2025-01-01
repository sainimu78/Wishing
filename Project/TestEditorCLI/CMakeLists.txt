cmake_minimum_required(VERSION 3.20.0)

include(../InitRootPath.cmake)

set(c_ProjectName TestEditorCLI)

include(${c_RootCMakeDirPath}/ProjectBegin.cmake)
project(${c_ProjectName})
include(${c_RootCMakeDirPath}/ProjectEnd.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${c_ProjectName})
endif()

add_subdirectory(TestEngine)
add_subdirectory(TestModule0)
add_subdirectory(${c_ProjectName})

include(${c_RootCMakeDirPath}/Setup.cmake)
include(${c_RootCMakeDirPath}/Release.cmake)