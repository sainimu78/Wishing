set(ProjectSrcRoot ${RootSourcePath}/CppProjectGenTool)

set(ModuleName CppProjectGen)

set(ModuleRootPath ${ProjectSrcRoot}/${ModuleName})
set(ModuleSourcePath ${ModuleRootPath})
set(ModuleIncludePath ${ModuleRootPath})

set(IncludePathsPrivate "")
set(IncludePathsPublic "")
list(APPEND IncludePathsPrivate ${ModuleSourcePath})
list(APPEND IncludePathsPrivate ${RootSourcePath})
list(APPEND IncludePathsPrivate ${RootSourcePath}/NiflectGen)
list(APPEND IncludePathsPublic ${ModuleIncludePath})

file(GLOB_RECURSE ModuleSources ${ModuleSourcePath}/*.cpp ${ModuleSourcePath}/*.h)
create_source_group(${ModuleSourcePath} ${ModuleSources})

set(SrcAll "")
list(APPEND SrcAll ${ModuleSources})

add_library(${ModuleName} SHARED ${SrcAll})

set_target_properties(${ModuleName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
)

target_include_directories(${ModuleName}
	PRIVATE ${IncludePathsPrivate}
	PUBLIC ${IncludePathsPublic}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DCPPPROJECTGEN_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)

