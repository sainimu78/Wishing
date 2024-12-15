cmake_minimum_required(VERSION 3.20.0)

include(../RootPathSetup.cmake)

include(${RootProjectPath}/CommonBeforeProject.cmake)
project(TestEditorCLI)
include(${RootProjectPath}/CommonAfterProject.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT TestEditorCLI)
endif()

add_subdirectory(TestEditorCLI)
add_subdirectory(TestEngine)
add_subdirectory(Base)
add_subdirectory(TestModule0)