cmake_minimum_required(VERSION 3.10.0)

include(../CommonBeforeProject.cmake)

project(NiflectGenTool)

include(../CommonAfterProject.cmake)

add_subdirectory(Niflect)
add_subdirectory(NiflectGen)
add_subdirectory(NiflectGenTool)
