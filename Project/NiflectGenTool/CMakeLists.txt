cmake_minimum_required(VERSION 3.10.0)

include(../RootPathSetup.cmake)

include(${RootProjectPath}/CommonBeforeProject.cmake)
project(NiflectGenTool)
include(${RootProjectPath}/CommonAfterProject.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT NiflectGenTool)
endif()

add_subdirectory(Base)
add_subdirectory(NiflectGen)
add_subdirectory(NiflectGenTool)
