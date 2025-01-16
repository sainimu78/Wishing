if(MSVC)
	set(ExeDirPathDebug I:/F/Fts/Proj/Test/Wishing/Build/Sample/AssetCreator/Windows/DefaultBuild/Debug/bin)
	set(ExeDirPathRelease I:/F/Fts/Proj/Test/Wishing/Build/Sample/AssetCreator/Windows/DefaultBuild/Release/bin)
	set(ExeFileName Creator.exe)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${ExeDirPathDebug},${ExeDirPathRelease}>"
	)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_COMMAND "$<IF:$<CONFIG:Debug>,${ExeDirPathDebug}/${ExeFileName},${ExeDirPathRelease}/${ExeFileName}>"
	)
endif()