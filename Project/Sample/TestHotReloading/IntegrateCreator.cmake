if(MSVC)
	get_filename_component(ExeDirPathDebug "../../../../Build/Sample/ContentCreator/Windows/DefaultBuild/Debug/bin" ABSOLUTE)
	get_filename_component(ExeDirPathRelease "../../../../Build/Sample/ContentCreator/Windows/DefaultBuild/Release/bin" ABSOLUTE)
	set(ExeFileName Editor.exe)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${ExeDirPathDebug},${ExeDirPathRelease}>"
	)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_COMMAND "$<IF:$<CONFIG:Debug>,${ExeDirPathDebug}/${ExeFileName},${ExeDirPathRelease}/${ExeFileName}>"
	)

	get_filename_component(ProjectDirPath "../../../../Build/Sample/TestHotReloading" ABSOLUTE)
	set(ListOptCreatorOption "")
	list(APPEND ListOptCreatorOption "-p" ${ProjectDirPath})
	set(OptCreatorOption "")
	foreach(It IN LISTS ListOptCreatorOption)
		set(OptCreatorOption "${OptCreatorOption} ${It}")
	endforeach()
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_COMMAND_ARGUMENTS "$<IF:$<CONFIG:Debug>,${OptCreatorOption},${OptCreatorOption}>"
	)
endif()