cmake_minimum_required(VERSION 3.10.0)

set(ProjectSrcRoot ${RootSourcePath}/CppProjectGenTool)

set(ModuleName CppProjectGenCLI)

set(ModuleRootPath ${ProjectSrcRoot}/${ModuleName})
set(SourcePath ${ModuleRootPath})
file(GLOB_RECURSE ModuleSrc ${SourcePath}/*.cpp ${SourcePath}/*.h)

#set(CodeWriterSourcePath ${RootSourcePath}/NiflectGen/CodeWriter)
#file(GLOB_RECURSE CodeWriterSrc ${CodeWriterSourcePath}/*.cpp ${CodeWriterSourcePath}/*.h)

set(SrcAll "")
list(APPEND SrcAll ${ModuleSrc})
#list(APPEND SrcAll ${CodeWriterSrc})

create_source_group(${ModuleRootPath} ${SrcAll})

add_executable(${ModuleName} ${SrcAll})

target_link_libraries(${ModuleName} PRIVATE Niflect)
target_link_libraries(${ModuleName} PRIVATE CppProjectGen)

target_include_directories(${ModuleName}
	PRIVATE ${ProjectSrcRoot}
)

if(MSVC)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG},${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}>"
	)
endif()