if(MSVC)
	get_filename_component(ExeDirPathDebug "../../../../Build/Sample/AssetCreator/Windows/DefaultBuild/Debug/bin" ABSOLUTE)
	get_filename_component(ExeDirPathRelease "../../../../Build/Sample/AssetCreator/Windows/DefaultBuild/Release/bin" ABSOLUTE)
	set(ExeFileName Editor.exe)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${ExeDirPathDebug},${ExeDirPathRelease}>"
	)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_COMMAND "$<IF:$<CONFIG:Debug>,${ExeDirPathDebug}/${ExeFileName},${ExeDirPathRelease}/${ExeFileName}>"
	)
endif()