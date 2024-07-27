set(ExeName Editor)
file(GLOB SrcAll "*.cpp" "*.h") 
add_executable(${ExeName} ${SrcAll})

target_link_libraries(${ExeName} PRIVATE Engine)

target_include_directories(${ExeName}
	#PRIVATE ${ProjectSourcePath}
	#PRIVATE ${S3EngineIncludePath}
	##todo: 现代码未合并到引擎, 因此暂使用SampleTest的路径, 合并后可移除
	#PRIVATE ${BaseSourcePath}
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)
