cmake_minimum_required(VERSION 3.20.0)

set(ModuleName Editor)

set(ModuleRootPath ${ProjectRootSourcePath}/${ModuleName})
set(SourcePath ${ModuleRootPath}/src)
set(IncludePath ${ModuleRootPath}/include)

file(GLOB_RECURSE ModuleSrc ${SourcePath}/*.cpp ${SourcePath}/*.h)
create_source_group(${SourcePath} ${ModuleSrc})
file(GLOB_RECURSE ModuleInclude ${IncludePath}/*.h)
create_source_group(${IncludePath} ${ModuleInclude})
set(SrcAll "")
list(APPEND SrcAll ${ModuleSrc})
list(APPEND SrcAll ${ModuleInclude})

set(ModuleGenPath ${ProjectGeneratedRootPath}/${ModuleName}/_GenSource)
set(GenIncludePath ${ModuleGenPath}/include)
#beign, 用于模式 EGeneratingHeaderAndSourceFileMode::ESourceAndHeader, 将生成文件加到模块
#file(GLOB_RECURSE GeneratedSrc ${ModuleGenPath}/*.cpp ${ModuleGenPath}/*.h)
#create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#list(APPEND SrcAll ${GeneratedSrc})
#end

add_executable(${ModuleName} ${SrcAll})

if (WIN32)
	set_target_properties(${ModuleName} PROPERTIES
		LINK_FLAGS "/SUBSYSTEM:WINDOWS"
	)
endif()

## Qt 6.8.1 requires
#if(MSVC)
#    #add_compile_options(/Zc:__cplusplus)
#	target_compile_options(${ModuleName} PRIVATE /Zc:__cplusplus)
#	target_compile_options(${ModuleName} PRIVATE /permissive-)
#endif()

target_include_directories(${ModuleName}
	PRIVATE ${SourcePath}
	PRIVATE ${SourcePath}/Widget
	PUBLIC ${IncludePath}
)

target_include_directories(${ModuleName}
	PRIVATE ${ModuleGenPath}
	PUBLIC ${GenIncludePath}
)

target_link_libraries(${ModuleName} PRIVATE Engine)
target_link_libraries(${ModuleName} PRIVATE Niflect)

include(Licensed_Qt.cmake)

set(ArgsModuleInclude "")
foreach(It IN LISTS ModuleInclude)
    list(APPEND ArgsModuleInclude "-h" "${It}")
endforeach()

set(ToolRelPathForTest Linux/Make_x64)
set(ExeExt )
if (WIN32)
	set(ExeExt .exe)
	set(ToolRelPathForTest Windows/vs2022_x64)
endif()

set(NiflectGeneratedModulePrivateH ${ModuleGenPath}/${ModuleName}_private.h)
add_custom_command(
    OUTPUT "${NiflectGeneratedModulePrivateH}"
    COMMAND "${RootSourcePath}/../Build/NiflectGenTool/${ToolRelPathForTest}/Debug/NiflectGenTool/NiflectGenTool${ExeExt}" 
            -n ${ModuleName} 
            ${ArgsModuleInclude}
            -a "${RootSourcePath}/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h" 
            -t "${RootSourcePath}/Niflect/include" 
            -I "${IncludePath}" 
            -g "${ProjectGeneratedRootPath}"
			-gbt 
    DEPENDS ${ModuleInclude}
    COMMENT "NiflectGenTool generating ..."
)

add_custom_target(NiflectGenTool_${ModuleName} DEPENDS "${NiflectGeneratedModulePrivateH}")
set_target_properties(NiflectGenTool_${ModuleName} PROPERTIES FOLDER "AutoGen")
add_dependencies(${ModuleName} NiflectGenTool_${ModuleName})

#if(UNIX)
#	file(MAKE_DIRECTORY ${NiflectGeneratedRootPath}) # 由于创建目录的函数实现存在缺陷, NiflectGenTool 并发执行时出现首次创建不存在的输出目录失败与之后写文件失败, 因此仅在 UNIX 上通过 cmake 创建输出目录
#endif()

if(MSVC)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG},${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}>"
	)
endif()