set(ModuleName WishingEngine)

set(ModuleRootDirPath ${c_RootSourceDirPath}/${ModuleName})
set(ModuleSourceDirPath ${ModuleRootDirPath}/src)
set(ModuleHeaderDirPath ${ModuleRootDirPath}/include)

set(IncludePathsPrivate "")
set(IncludePathsPublic "")
list(APPEND IncludePathsPrivate ${ModuleSourceDirPath})
list(APPEND IncludePathsPublic ${ModuleHeaderDirPath})

file(GLOB_RECURSE ModuleSources ${ModuleSourceDirPath}/*.cpp ${ModuleSourceDirPath}/*.h)
create_source_group(${ModuleSourceDirPath} ${ModuleSources})
file(GLOB_RECURSE ModuleHeaders ${ModuleHeaderDirPath}/*.h)
create_source_group(${ModuleHeaderDirPath} ${ModuleHeaders})
set(SrcAll "")
list(APPEND SrcAll ${ModuleSources})
list(APPEND SrcAll ${ModuleHeaders})

add_library(${ModuleName} SHARED ${SrcAll})

#target_precompile_headers(${ModuleName} PRIVATE ${ModuleSourceDirPath}/EngineDevelopmentMacro.h)

target_include_directories(${ModuleName}
	PRIVATE ${IncludePathsPrivate}
	PUBLIC ${IncludePathsPublic}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DWISHINGENGINE_EXPORTS
)

#list(APPEND v_ListAccessorSettingHeaderFilePath ${c_RootThirdPartyDirPath}/Niflect/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h)
list(APPEND v_ListAccessorSettingHeaderFilePath ${ModuleHeaderDirPath}/WishingEngineAccessorSetting.h)
#list(APPEND v_ListModuleIncludeDirPath ${IncludePathsPrivate})
#list(APPEND v_ListModuleIncludeDirPath ${IncludePathsPublic})
list(APPEND v_ListModuleHeaderFilePath ${ModuleHeaders})
set(v_ModuleAPIMacro WISHINGENGINE_API)
set(v_ModuleAPIMacroHeaderFilePath ${ModuleHeaderDirPath}/WishingEngineCommon.h)
list(APPEND v_ListToolOption "-gmi")
include(${c_RootProjectDirPath}/Niflect/Default.cmake)

#if(WIN32)
#	# #include "boost/asio.hpp" requires
#	target_compile_definitions(${ModuleName} PRIVATE _WIN32_WINNT=0x0601)
#    #add_definitions(-D_WIN32_WINNT=0x0601)
#endif()
include(${c_RootThirdPartyDirPath}/boost/boost_1_73_0/Static.cmake)

#target_link_libraries(${ModuleName} PRIVATE TestModule1)
#include(${c_ProjectDirPath}/TestModule1/Shared.cmake)