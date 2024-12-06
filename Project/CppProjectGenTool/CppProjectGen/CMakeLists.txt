cmake_minimum_required(VERSION 3.10.0)

set(ModuleName CppProjectGen)

set(SourcePath ${RootSourcePath}/${ModuleName})

file(GLOB_RECURSE SrcAll ${SourcePath}/*.cpp ${SourcePath}/*.h)

create_source_group(${RootSourcePath} ${SrcAll})

add_library(${ModuleName} SHARED ${SrcAll})

set_target_properties(${ModuleName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
)

target_include_directories(${ModuleName}
	PUBLIC ${RootSourcePath}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DCPPPROJECTGEN_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)

