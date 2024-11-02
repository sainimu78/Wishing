cmake_minimum_required(VERSION 3.20.0)

include(../RootPathSetup.cmake)

include(${RootProjectPath}/CommonBeforeProject.cmake)
project(Interedit)
include(${RootProjectPath}/CommonAfterProject.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Editor)
endif()

add_subdirectory(Editor)
add_subdirectory(Engine)
add_subdirectory(Base)
add_subdirectory(TestModule0)