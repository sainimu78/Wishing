cmake_minimum_required(VERSION 3.10.0)

set(ModuleName Editor)

set(SourcePath ${RootSourcePath}/Editor)

file(GLOB_RECURSE SrcAll ${SourcePath}/*.cpp ${SourcePath}/*.h)
#list(APPEND SrcAll ${SrcDefault})

create_source_group(${RootSourcePath} ${SrcAll})

add_executable(${ModuleName} ${SrcAll})
#set_target_properties(${ModuleName} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${ModuleName} PRIVATE Engine)
target_link_libraries(${ModuleName} PRIVATE Niflect)
target_link_libraries(${ModuleName} PRIVATE TestModule0)

target_include_directories(${ModuleName}
	#PRIVATE ${RootSourcePath}
	#PRIVATE ${S3EngineIncludePath}
	##todo: 现代码未合并到引擎, 因此暂使用SampleTest的路径, 合并后可移除
	#PRIVATE ${BaseSourcePath}
	PRIVATE ${RootSourcePath}
)

if(MSVC)
	set_target_properties(Editor PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release>"
	)
endif()