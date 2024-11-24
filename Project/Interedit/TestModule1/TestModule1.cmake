cmake_minimum_required(VERSION 3.20.0)

set(ModuleName TestModule1)

set(SourcePath ${RootSourcePath}/${ModuleName})

file(GLOB_RECURSE ModuleSources ${SourcePath}/*.cpp)
file(GLOB_RECURSE ModuleHeaders ${SourcePath}/*.h)

set(SrcAll "")
list(APPEND SrcAll ${ModuleSources})
list(APPEND SrcAll ${ModuleHeaders})
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
	PUBLIC ${RootSourcePath}
)

target_include_directories(${ModuleName}
	PRIVATE ${ModuleGenPath}
	PUBLIC ${GenIncludePath}
)

target_compile_definitions(${ModuleName}
	PRIVATE -DTESTMODULE1_EXPORTS
)

target_link_libraries(${ModuleName} PRIVATE Niflect)

set(ArgsModuleHeaders "")
foreach(It IN LISTS ModuleHeaders)
    list(APPEND ArgsModuleHeaders "-h" "${It}")
endforeach()

set(NiflectGeneratedModulePrivateH ${NiflectGeneratedRootPath}/${ModuleName}/${ModuleName}_private.h)
add_custom_command(
    OUTPUT "${NiflectGeneratedModulePrivateH}"
    COMMAND "${RootSourcePath}/../Build/NiflectGenTool/Windows/vs2022_x64/Debug/NiflectGenTool/NiflectGenTool.exe" 
            -n ${ModuleName} 
            ${ArgsModuleHeaders}
            -am TESTMODULE1_API 
            -amh "${SourcePath}/TestModule1Common.h" 
            -a "${RootSourcePath}/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h" 
            -I "${RootSourcePath}" 
            -I "${RootSourcePath}/Niflect/include" 
            -g "${NiflectGeneratedRootPath}"
    DEPENDS ${ModuleHeaders}
    COMMENT "NiflectGenTool generating ..."
)

add_custom_target(NiflectGenTool ALL DEPENDS "${NiflectGeneratedModulePrivateH}")
add_dependencies(${ModuleName} NiflectGenTool) #使在 vs 中按 F5 也能触发生成