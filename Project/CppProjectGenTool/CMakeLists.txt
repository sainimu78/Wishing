cmake_minimum_required(VERSION 3.10.0)

include(../RootPathSetup.cmake)

set(ProjectName CppProjectGenTool)
include(${RootProjectPath}/CommonBeforeProject.cmake)
project(${ProjectName})
include(${RootProjectPath}/CommonAfterProject.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT CppProjectGenCLI)
endif()

include(${RootProjectPath}/Niflect/Niflect.cmake)
add_subdirectory(CppProjectGen)
add_subdirectory(CppProjectGenCLI)
