cmake_minimum_required(VERSION 3.20.0)

set(ModuleName TestModule1)

set(SourcePath ${RootSourcePath}/${ModuleName}/src)
set(IncludePath ${RootSourcePath}/${ModuleName}/include)

file(GLOB_RECURSE ModuleSrc ${SourcePath}/*.cpp ${SourcePath}/*.h)
file(GLOB_RECURSE ModuleInclude ${IncludePath}/*.h)
set(SrcAll "")
list(APPEND SrcAll ${ModuleSrc})
list(APPEND SrcAll ${ModuleInclude})
create_source_group(${RootSourcePath} ${SrcAll})

get_filename_component(NiflectGeneratedRootPath "${RootSourcePath}/../Generated/NiflectGenerated" ABSOLUTE)
set(ModuleGenPath ${NiflectGeneratedRootPath}/${ModuleName})
set(GenIncludePath ${ModuleGenPath}/_GenInclude)
#beign, 用于模式 EGeneratingHeaderAndSourceFileMode::ESourceAndHeader, 将生成文件加到模块
#file(GLOB_RECURSE GeneratedSrc ${ModuleGenPath}/*.cpp ${ModuleGenPath}/*.h)
#create_source_group(${NiflectGeneratedRootPath} ${GeneratedSrc})
#list(APPEND SrcAll ${GeneratedSrc})
#end

add_library(${ModuleName} SHARED ${SrcAll})

set_target_properties(${ModuleName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
)

target_include_directories(${ModuleName}
	PRIVATE ${SourcePath}
	PUBLIC ${IncludePath}
)

target_include_directories(${ModuleName}
	PRIVATE ${ModuleGenPath}
	PUBLIC ${GenIncludePath}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DTESTMODULE1_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)

set(ArgsModuleInclude "")
foreach(It IN LISTS ModuleInclude)
    list(APPEND ArgsModuleInclude "-h" "${It}")
endforeach()

set(NiflectGeneratedModulePrivateH ${NiflectGeneratedRootPath}/${ModuleName}/${ModuleName}_private.h)
add_custom_command(
    OUTPUT "${NiflectGeneratedModulePrivateH}"
    COMMAND "${RootSourcePath}/../Build/NiflectGenTool/Windows/vs2022_x64/Debug/NiflectGenTool/NiflectGenTool.exe" 
            -n ${ModuleName} 
            ${ArgsModuleInclude}
            -am TESTMODULE1_API 
            -amh "${IncludePath}/TestModule1Common.h" 
            -a "${RootSourcePath}/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h" 
            -t "${RootSourcePath}/Niflect/include" 
            -I "${IncludePath}" 
            -g "${NiflectGeneratedRootPath}"
    DEPENDS ${ModuleInclude}
    COMMENT "NiflectGenTool generating ..."
)

add_custom_target(NiflectGenTool ALL DEPENDS "${NiflectGeneratedModulePrivateH}")
add_dependencies(${ModuleName} NiflectGenTool) #使在 vs 中按 F5 也能触发生成