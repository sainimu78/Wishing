
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
if (WIN32)
	set(ExeExt .exe)
endif()

set(GenToolName NiflectGenCLI)

set(GenToolExeName ${GenToolName}${ExeExt})
set(GenToolBinDirPathDebug ${NiflectRootPath}/Debug/bin)
set(GenToolBinDirPathRelease ${EditorBinDirPath}/Release/bin)
set(GenToolFilePathDebug ${GenToolBinDirPathDebug}/${GenToolExeName})
set(GenToolFilePathRelease ${GenToolBinDirPathRelease}/${GenToolExeName})
set(GenToolExe "$<$<CONFIG:Debug>:${GenToolFilePathDebug}>$<$<CONFIG:Release>:${GenToolFilePathRelease}>")

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

add_custom_command(
    OUTPUT "${GeneratedModulePrivateH}"
    COMMAND ${GenToolExe} 
            -n ${ModuleName} 
            ${OptModuleHeaders}
            ${ListOptModuleAPIMacro} 
            ${ListOptModuleAPIMacroHeader}
            ${OptAccessorSettingHeaders} 
            -t "${NiflectRootPath}/include" 
            ${OptModuleIncludePaths} 
            -g "${GenOutputDirPath}"
			-gbt 
			-debug 
    DEPENDS ${ModuleHeaders}
    COMMENT "${GenToolExe}: ${ModuleName}"
)

set(GenToolTargetName ${GenToolName}_${ModuleName})
add_custom_target(${GenToolTargetName} DEPENDS "${GeneratedModulePrivateH}")
set_target_properties(${GenToolTargetName} PROPERTIES FOLDER "AutoGen")
add_dependencies(${ModuleName} ${GenToolTargetName})