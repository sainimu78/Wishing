cmake_minimum_required(VERSION 3.10.0)

FUNCTION(create_source_group relativeSourcePath)
  FOREACH(currentSourceFile ${ARGN})
    FILE(RELATIVE_PATH folder ${relativeSourcePath} ${currentSourceFile})
    GET_FILENAME_COMPONENT(filename ${folder} NAME)
    STRING(REPLACE ${filename} "" folder ${folder})
    IF(NOT folder STREQUAL "")
      STRING(REGEX REPLACE "/+$" "" folderlast ${folder})
      STRING(REPLACE "/" "\\" folderlast ${folderlast})
      SOURCE_GROUP("${folderlast}" FILES ${currentSourceFile})
    ENDIF(NOT folder STREQUAL "")
  ENDFOREACH(currentSourceFile ${ARGN})
ENDFUNCTION(create_source_group)

project(Interedit)

set(AppOutputPath "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}")
set(ProjectSourcePath "${CMAKE_CURRENT_SOURCE_DIR}")
#set(EngineSourcePath "${ProjectSourcePath}/../Engine")
#set(DependenciesPath "${EngineSourcePath}/Dependencies")
#set(S3EngineIncludePath "${EngineSourcePath}/S3Engine")
#set(BaseSourcePath "${EngineSourcePath}/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${AppOutputPath}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${AppOutputPath}/Release)

add_subdirectory(Editor)
add_subdirectory(Engine)