install(TARGETS ${ModuleName}
	RUNTIME DESTINATION "${c_ProjectInstallingTargetDirPath}/${c_BinDirName}"
)

if(WIN32)
	install(FILES "$<TARGET_FILE_DIR:${ModuleName}>/${ModuleName}.pdb"
		DESTINATION "${c_ProjectInstallingTargetDirPath}/${c_BinDirName}"
		CONFIGURATIONS Debug
	)
endif()