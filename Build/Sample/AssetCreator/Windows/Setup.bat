@echo off
setlocal

set Arch=%2
set ToolsetAndArch=%1_%Arch%
set Platform=Windows
set ToolDirPath=%cd%
set path=%ToolDirPath%;%path%
set UserName=WishingContributor
set Password=1

set StorageDirPath=http://192.168.245.158/sainimu78_Storage

set Name7zExe=7za.exe
set Storage7zDirPath=%StorageDirPath%/Tool/%Platform%/7z
set Dst7zExeFilePath=%ToolDirPath%\%Name7zExe%
curl -u %UserName%:%Password% -L -o "%Dst7zExeFilePath%" "%Storage7zDirPath%/%Name7zExe%"

set DependencyName_T0T=Niflect
set SrcRootDirPath_T0T=%StorageDirPath%/Release/%Platform%
set DstRootDirPath_T0T=%cd%\..\..\..\..\ThirdParty\%DependencyName_T0T%
set SrcExtractedDirPath_T0T=%DstRootDirPath_T0T%\%DependencyName_T0T%
set ZipFileName_T0T=%DependencyName_T0T%.zip
set SrcZipFilePath_T0T=%SrcRootDirPath_T0T%/%ZipFileName_T0T%
set DstZipFilePath_T0T=%DstRootDirPath_T0T%\%ZipFileName_T0T%
curl -u %UserName%:%Password% -L -o "%DstZipFilePath_T0T%" "%SrcZipFilePath_T0T%"
rmdir /s /q "%SrcExtractedDirPath_T0T%"
%Name7zExe% x "%DstZipFilePath_T0T%" -o"%DstRootDirPath_T0T%"
del "%DstZipFilePath_T0T%"

set DependencyName_T1T=Qt_5_8_0
set SrcRootDirPath_T1T=%StorageDirPath%/ThirdParty/Qt/%Platform%
set DstRootDirPath_T1T=%cd%\..\..\..\..\ThirdParty\Qt\%DependencyName_T1T%
set SrcExtractedDirPath_T1T=%DstRootDirPath_T1T%\%DependencyName_T1T%
set ZipFileName_T1T=%DependencyName_T1T%.zip
set SrcZipFilePath_T1T=%SrcRootDirPath_T1T%/%ZipFileName_T1T%
set DstZipFilePath_T1T=%DstRootDirPath_T1T%\%ZipFileName_T1T%
curl -u %UserName%:%Password% -L -o "%DstZipFilePath_T1T%" "%SrcZipFilePath_T1T%"
rmdir /s /q "%SrcExtractedDirPath_T1T%"
%Name7zExe% x "%DstZipFilePath_T1T%" -o"%DstRootDirPath_T1T%"
del "%DstZipFilePath_T1T%"

del "%Dst7zExeFilePath%"

::--------------------------------------------------------------

set DstBinPathDebug=%cd%\%ToolsetAndArch%\Debug\bin
set DstBinPathRelease=%cd%\%ToolsetAndArch%\Release\bin

set SrcBuildArchDirPath_T0T=%SrcExtractedDirPath_T0T%\build\%Platform%\%Arch%
set SrcBinPathDebug_T0T=%SrcBuildArchDirPath_T0T%\Debug\bin
set SrcBinPathRelease_T0T=%SrcBuildArchDirPath_T0T%\Release\bin
xcopy /E /y "%SrcBinPathDebug_T0T%\%DependencyName_T0T%.dll" "%DstBinPathDebug%\"
xcopy /E /y "%SrcBinPathDebug_T0T%\%DependencyName_T0T%.pdb" "%DstBinPathDebug%\"
xcopy /E /y "%SrcBinPathRelease_T0T%\%DependencyName_T0T%.dll" "%DstBinPathRelease%\"

set SrcBuildArchDirPath_T1T=%SrcExtractedDirPath_T1T%\build\5.8\msvc2015_64
set SrcBinPath_T1T=%SrcBuildArchDirPath_T1T%\bin
xcopy /E /y "%SrcBinPath_T1T%\Qt*d.dll" "%DstBinPathDebug%\"
xcopy /E /y "%SrcBinPath_T1T%\Qt*d.pdb" "%DstBinPathDebug%\"
xcopy /E /y "%SrcBinPath_T1T%\Qt*.dll" "%DstBinPathRelease%\"
del /q "%DstBinPathRelease%\Qt*d.dll"

endlocal