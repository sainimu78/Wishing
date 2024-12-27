
set(LibName Niflect)
set(LibRootPath ${ProjectRootThirdPartyPath}/${LibName}/${LibName})

target_link_libraries(${ModuleName} PRIVATE ${LibName})

target_include_directories(${ModuleName} PRIVATE "${LibRootPath}/include")

if(UNIX)
	message(STATUS "Target Is on UNIX")
	set(OsType Linux)
	set(DlPost .so)
	set(SlPost .a)
elseif(APPLE)
	message(STATUS "Target Is on APPLE")
	message(FATAL_ERROR "OsType & DynamicLibraryPrefix & DynamicLibraryPostfix are not specified")
elseif(WIN32)
	message(STATUS "Target Is on WIN32")
	set(OsType Windows)
	set(DlPost .dll)
	set(SlPost .lib)
endif()

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")	
	if(WIN32)
		set(libclangLibDebug "${LibRootPath}/build/Windows/x64/Debug/bin/${LibName}${SlPost}")
		set(libclangLibRelease "${LibRootPath}/build/Windows/x64/Release/bin/${LibName}${SlPost}")
		set_target_properties(${LibName} PROPERTIES
			IMPORTED_IMPLIB_DEBUG "${libclangLibDebug}"
			IMPORTED_IMPLIB_RELEASE "${libclangLibRelease}"
			IMPORTED_IMPLIB_RELWITHDEBINFO "${libclangLibDebug}"
			IMPORTED_IMPLIB_MINSIZEREL "${libclangLibRelease}"
		)
		target_include_directories(${ModuleName} PRIVATE "${LibPath}/include")
	else()
		set(libclangBinDebug "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/${LibName}${DlPost}")
		set(libclangBinRelease "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/${LibName}${DlPost}")
		set_target_properties(${LibName} PROPERTIES
			IMPORTED_LOCATION_DEBUG "${libclangBinDebug}"
			IMPORTED_LOCATION_RELEASE "${libclangBinRelease}"
			IMPORTED_LOCATION_RELWITHDEBINFO "${libclangBinDebug}"
			IMPORTED_LOCATION_MINSIZEREL "${libclangBinRelease}"
		)
	endif()
	
	target_link_libraries(${ModuleName} PRIVATE ${LibName})
else()
	message(ERROR "asdf")
endif()
