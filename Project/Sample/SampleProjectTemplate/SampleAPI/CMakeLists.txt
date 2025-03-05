set(ModuleName SampleAPI)

set(ModuleRootPath ${c_SampleRootSourceDirPath}/${ModuleName})
set(ModuleSourcePath ${ModuleRootPath}/src)
set(ModuleIncludePath ${ModuleRootPath}/include)

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

add_library(${ModuleName} SHARED ${SrcAll})

target_include_directories(${ModuleName}
	PRIVATE ${IncludePathsPrivate}
	PUBLIC ${IncludePathsPublic}
)

target_compile_definitions(${ModuleName} PRIVATE -DSAMPLEAPI_EXPORTS)

list(APPEND v_ListAccessorSettingHeaderFilePath ${c_RootThirdPartyDirPath}/Niflect/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h)
#list(APPEND v_ListModuleIncludeDirPath ${IncludePathsPublic})
list(APPEND v_ListModuleHeaderFilePath ${ModuleHeaders})
#set(v_ModuleAPIMacro SAMPLEAPI_API)
#set(v_ModuleAPIMacroHeaderFilePath ${ModuleIncludePath}/SampleAPICommon.h)
#set(v_ToGenApiModuleHeader TRUE)
#list(APPEND v_ListToolOption "-gsm")

include(${c_RootProjectDirPath}/Niflect/Default.cmake)

include(${c_ProjectDirPath}/Install.cmake)