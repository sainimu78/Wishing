
set(GenToolName NiflectGenTool)
set(GenToolRootPath ${ProjectRootThirdPartyPath}/${GenToolName}/${GenToolName})
set(NiflectRootPath ${ProjectRootThirdPartyPath}/Niflect/Niflect)

set(GenOutputDirPath ${ProjectGeneratedRootPath}/${ModuleName})
set(GenSourcePrivate ${GenOutputDirPath}/_GenSource)
set(GenSourcePublic ${GenSourcePrivate}/include)
#beign, 用于模式 EGeneratingHeaderAndSourceFileMode::ESourceAndHeader, 将生成文件加到模块
#file(GLOB_RECURSE GeneratedSrc ${GenSourcePrivate}/*.cpp ${GenSourcePrivate}/*.h)
#create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#list(APPEND SrcAll ${GeneratedSrc})
#end

target_include_directories(${ModuleName}
	PRIVATE ${GenSourcePrivate}
	PUBLIC ${GenSourcePublic}
)

set(OptModuleHeaders "")
foreach(It IN LISTS ModuleHeaders)
    list(APPEND OptModuleHeaders "-h" "${It}")
endforeach()
set(OptModuleIncludePaths "")
foreach(It IN LISTS IncludePathsPrivate)
	list(APPEND OptModuleIncludePaths "-I" "${It}")
endforeach()
foreach(It IN LISTS IncludePathsPublic)
	list(APPEND OptModuleIncludePaths "-I" "${It}")
endforeach()

set(OptAccessorSettingHeaders "")
foreach(It IN LISTS AccessorSettingHeaders)
	list(APPEND OptAccessorSettingHeaders "-a" "${It}")
endforeach()
set(ListOptModuleAPIMacro "")
if(ModuleAPIMacro)
    list(APPEND ListOptModuleAPIMacro "-am" "${ModuleAPIMacro}")
endif()
set(ListOptModuleAPIMacroHeader "")
if(ModuleAPIMacroHeader)
    list(APPEND ListOptModuleAPIMacroHeader "-amh" "${ModuleAPIMacroHeader}")
endif()

set(ExeExt )
set(Platform Windows)
if(WIN32)
	message(STATUS "Target Is on WIN32")
	set(Platform Windows)
	set(DlPost .dll)
	set(SlPost .lib)
	set(ExeExt .exe)
elseif(UNIX)
	message(STATUS "Target Is on UNIX")
	set(Platform Linux)
	set(DlPost .so)
	set(SlPost .a)
elseif(APPLE)
	message(STATUS "Target Is on APPLE")
	message(FATAL_ERROR "Platform & DynamicLibraryPrefix & DynamicLibraryPostfix are not specified")
endif()

set(Arch x86)
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	set(Arch x64)
endif()

#begin, 区分 Debug 与 Release 两种版本的 GenTool, add_custom_command 中变量不用引号
#set(GenToolExeName ${GenToolName}${ExeExt})
#set(GenToolBinDirPathDebug ${GenToolRootPath}/build/${Platform}/${Arch}/Debug/bin)
#set(GenToolBinDirPathRelease ${GenToolRootPath}/build/${Platform}/${Arch}/Release/bin)
#set(GenToolFilePathDebug ${GenToolBinDirPathDebug}/${GenToolExeName})
#set(GenToolFilePathRelease ${GenToolBinDirPathRelease}/${GenToolExeName})
#set(GenToolExeFilePath "$<$<CONFIG:Debug>:${GenToolFilePathDebug}>$<$<CONFIG:Release>:${GenToolFilePathRelease}>")
#end

set(GenToolExeName ${GenToolName}${ExeExt})
set(GenToolExeFilePath ${GenToolRootPath}/build/${Platform}/${Arch}/Release/bin/${GenToolExeName})

set(GeneratedModulePrivateH ${GenSourcePrivate}/${ModuleName}_private.h)

#message(${ModuleName})
#foreach(It IN LISTS OptModuleHeaders)
#	message(${It})
#endforeach()
#foreach(It IN LISTS ListOptModuleAPIMacro)
#	message(${It})
#endforeach()
#foreach(It IN LISTS ListOptModuleAPIMacroHeader)
#	message(${It})
#endforeach()
#foreach(It IN LISTS OptAccessorSettingHeaders)
#	message(${It})
#endforeach()
#message("${NiflectRootPath}/include")
#foreach(It IN LISTS OptModuleIncludePaths)
#	message(${It})
#endforeach()

set(GenToolDebugMode "-debuggerAttaching")
set(ListOptGenToolDebugMode "")
if(GenToolDebugMode)
	list(APPEND ListOptGenToolDebugMode cmd.exe /C start)
endif()

add_custom_command(
    OUTPUT "${GeneratedModulePrivateH}"
    COMMAND ${ListOptGenToolDebugMode} "${GenToolExeFilePath}" 
            -n ${ModuleName} 
            ${OptModuleHeaders}
            ${ListOptModuleAPIMacro} 
            ${ListOptModuleAPIMacroHeader}
            ${OptAccessorSettingHeaders} 
            -t "${NiflectRootPath}/include" 
            ${OptModuleIncludePaths} 
            -g "${GenOutputDirPath}"
			-gbt 
			${GenToolDebugMode} 
    DEPENDS ${ModuleHeaders}
    COMMENT "${GenToolName}: ${ModuleName}"
)

set(GenToolTargetName ${GenToolName}_${ModuleName})
add_custom_target(${GenToolTargetName} DEPENDS "${GeneratedModulePrivateH}")
set_target_properties(${GenToolTargetName} PROPERTIES FOLDER "AutoGen")
add_dependencies(${ModuleName} ${GenToolTargetName})