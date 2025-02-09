set(ModuleName TestEngine)

set(ModuleRootPath ${c_RootSourceDirPath}/${ModuleName})
set(ModuleSourcePath ${ModuleRootPath}/src)
set(ModuleIncludePath ${ModuleRootPath}/include)

set(IncludePathsPrivate "")
set(IncludePathsPublic "")
list(APPEND IncludePathsPrivate ${ModuleSourcePath})
list(APPEND IncludePathsPrivate ${c_RootSourceDirPath}/TestModule1/include)
list(APPEND IncludePathsPublic ${ModuleIncludePath})

file(GLOB_RECURSE ModuleSources ${ModuleSourcePath}/*.cpp ${ModuleSourcePath}/*.h)
create_source_group(${ModuleSourcePath} ${ModuleSources})
file(GLOB_RECURSE ModuleHeaders ${ModuleIncludePath}/*.h)
create_source_group(${ModuleIncludePath} ${ModuleHeaders})
set(SrcAll "")
list(APPEND SrcAll ${ModuleSources})
list(APPEND SrcAll ${ModuleHeaders})

add_library(${ModuleName} SHARED ${SrcAll})

target_precompile_headers(${ModuleName} PRIVATE ${ModuleSourcePath}/EngineDevelopmentMacro.h)

#set_target_properties(${ModuleName} PROPERTIES 
#    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
#    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
#)

target_include_directories(${ModuleName}
	PRIVATE ${IncludePathsPrivate}
	PUBLIC ${IncludePathsPublic}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DENGINE_EXPORTS
	PRIVATE -DENGINE_C_EXPORTS
)
target_link_libraries(${ModuleName} PRIVATE TestModule1)

#if(UNIX)
#	file(MAKE_DIRECTORY ${NiflectGeneratedRootPath}) # 由于创建目录的函数实现存在缺陷, NiflectGenTool 并发执行时出现首次创建不存在的输出目录失败与之后写文件失败, 因此仅在 UNIX 上通过 cmake 创建输出目录
#endif()

list(APPEND v_ListAccessorSettingHeaderFilePath ${ModuleIncludePath}/EngineAccessorSetting.h)
list(APPEND v_ListModuleIncludeDirPath ${IncludePathsPrivate})
list(APPEND v_ListModuleIncludeDirPath ${IncludePathsPublic})
list(APPEND v_ListModuleHeaderFilePath ${ModuleHeaders})
set(v_ModuleAPIMacro ENGINE_API)
set(v_ModuleAPIMacroHeaderFilePath ${ModuleIncludePath}/Engine/EngineCommon.h)

include(${c_RootProjectDirPath}/Niflect/Default.cmake)

include(${c_ProjectDirPath}/Install.cmake)

include(${c_ProjectDirPath}/TestModule1/Shared.cmake)