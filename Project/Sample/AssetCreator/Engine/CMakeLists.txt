cmake_minimum_required(VERSION 3.20.0)

set(ModuleName Engine)

set(ModuleRootPath ${c_SampleRootSourceDirPath}/${ModuleName})
set(ModuleSourcePath ${ModuleRootPath}/src)
set(ModuleIncludePath ${ModuleRootPath}/include)

set(v_ModuleAPIMacro ENGINE_API)
set(v_ModuleAPIMacroHeader ${ModuleIncludePath}/EngineCommon.h)
set(v_AccessorSettingHeaders "")
list(APPEND v_AccessorSettingHeaders ${c_RootThirdPartyDirPath}/Niflect/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h)

set(v_IncludePathsPrivate "")
set(v_IncludePathsPublic "")
list(APPEND v_IncludePathsPrivate ${ModuleSourcePath})
list(APPEND v_IncludePathsPublic ${ModuleIncludePath})

file(GLOB_RECURSE ModuleSources ${ModuleSourcePath}/*.cpp ${ModuleSourcePath}/*.h)
create_source_group(${ModuleSourcePath} ${ModuleSources})
file(GLOB_RECURSE v_ModuleHeaders ${ModuleIncludePath}/*.h)
create_source_group(${ModuleIncludePath} ${v_ModuleHeaders})
set(SrcAll "")
list(APPEND SrcAll ${ModuleSources})
list(APPEND SrcAll ${v_ModuleHeaders})

add_library(${ModuleName} SHARED ${SrcAll})

target_include_directories(${ModuleName}
	PRIVATE ${v_IncludePathsPrivate}
	PUBLIC ${v_IncludePathsPublic}
)


target_compile_definitions(${ModuleName} PRIVATE -DENGINE_EXPORTS)

include(${c_RootProjectDirPath}/Niflect/Default.cmake)

include(${c_ProjectDirPath}/Install.cmake)

#if(UNIX)
#	file(MAKE_DIRECTORY ${NiflectGeneratedRootPath}) # 由于创建目录的函数实现存在缺陷, NiflectGenTool 并发执行时出现首次创建不存在的输出目录失败与之后写文件失败, 因此仅在 UNIX 上通过 cmake 创建输出目录
#endif()

#if(MSVC)
#	set_target_properties(${ModuleName} PROPERTIES
#		VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG},${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}>"
#	)
#endif()