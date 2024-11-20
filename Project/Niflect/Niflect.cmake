set(ModuleName Niflect)

set(SourcePath ${RootSourcePath}/Niflect)

file(GLOB_RECURSE SrcAll ${SourcePath}/*.cpp ${SourcePath}/*.h)

create_source_group(${RootSourcePath} ${SrcAll})

add_library(${ModuleName} SHARED ${SrcAll})
set_target_properties(${ModuleName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
)

target_include_directories(${ModuleName}
	PUBLIC ${RootSourcePath}
)

if(CMAKE_CXX_COMPILER MATCHES "c\\+\\+$")
	message(STATUS "Using GCC")
	find_library(PTHREAD_LIB pthread)
	if (PTHREAD_LIB)
		target_link_libraries(${ModuleName} PRIVATE ${PTHREAD_LIB})
	endif()
elseif(CMAKE_CXX_COMPILER MATCHES "clang\\+\\+$")
	message(STATUS "Using Clang")
	
elseif(MSVC)
	message(STATUS "Using MSVC")
	
endif()

target_compile_definitions(${ModuleName} 
	PRIVATE -DNIFLECT_EXPORTS
)

set(LinkParentName ${ModuleName})