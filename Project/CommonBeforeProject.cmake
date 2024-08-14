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

if (WIN32)
	#避免如 freopen 的 Warning C4996
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(AppOutputPath ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME})
get_filename_component(RootSourcePath "${CMAKE_CURRENT_SOURCE_DIR}/../../Source" ABSOLUTE)

#set(EngineSourcePath "${RootSourcePath}/../Engine")
#set(DependenciesPath "${EngineSourcePath}/Dependencies")
#set(S3EngineIncludePath "${EngineSourcePath}/S3Engine")
#set(BaseSourcePath "${EngineSourcePath}/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${AppOutputPath})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)