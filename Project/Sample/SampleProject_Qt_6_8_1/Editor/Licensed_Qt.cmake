if(MSVC)
    target_compile_options(${ModuleName} PRIVATE /Zc:__cplusplus)
    target_compile_options(${ModuleName} PRIVATE /permissive-)
else()
	#This is required for Qt on Linux. cIf this option is not specified, the following error will occur:
	#/usr/include/x86_64-linux-gnu/qt5/QtCore/qglobal.h:1187:4: error: #error "You must build your code with position independent code if Qt was built with -reduce-relocations. " "Compile your code with -fPIC (-fPIE is not enough)."
	#1187 | #  error "You must build your code with position independent code if Qt was built with -reduce-relocations. "
	#target_compile_options(${ModuleName} PRIVATE -fPIC)
endif()
include(${c_RootThirdPartyDirPath}/Qt/Qt_6_8_1/Shared.cmake)