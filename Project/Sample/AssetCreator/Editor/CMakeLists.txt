cmake_minimum_required(VERSION 3.20.0)

set(ModuleName Editor)

set(ModuleRootPath ${ProjectRootSourcePath}/${ModuleName})
set(ModuleSourcePath ${ModuleRootPath}/src)
set(ModuleIncludePath ${ModuleRootPath}/include)

set(AccessorSettingHeaders "")
list(APPEND AccessorSettingHeaders ${ProjectRootThirdPartyPath}/Niflect/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h)

set(IncludePathsPrivate "")
set(IncludePathsPublic "")
list(APPEND IncludePathsPrivate ${ModuleSourcePath})
list(APPEND IncludePathsPublic ${ModuleIncludePath})

file(GLOB_RECURSE ModuleSources ${ModuleSourcePath}/*.cpp ${ModuleSourcePath}/*.h)
create_source_group(${ModuleSourcePath} ${ModuleSources})
file(GLOB_RECURSE ModuleHeaders ${ModuleIncludePath}/*.h)
create_source_group(${ModuleIncludePath} ${ModuleHeaders})
set(SrcAll "")
list(APPEND SrcAll ${ModuleSources})
list(APPEND SrcAll ${ModuleHeaders})

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
	PRIVATE ${IncludePathsPrivate}
	PUBLIC ${IncludePathsPublic}
)

include(../Base/Default.cmake)
include(Licensed_Qt.cmake)

target_link_libraries(${ModuleName} PRIVATE Engine)

#if(UNIX)
#	file(MAKE_DIRECTORY ${NiflectGeneratedRootPath}) # 由于创建目录的函数实现存在缺陷, NiflectGenTool 并发执行时出现首次创建不存在的输出目录失败与之后写文件失败, 因此仅在 UNIX 上通过 cmake 创建输出目录
#endif()

if(MSVC)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG},${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}>"
	)
endif()