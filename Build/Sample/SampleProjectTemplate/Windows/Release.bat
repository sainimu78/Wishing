@echo off
set ProjectDirPath=..\..\..\..\..\Project\Sample\SampleProjectTemplate
set BuildDirPath=DefaultBuild
set InstallPrefix=Installed
set OldDirPath=%cd%

cd %BuildDirPath%
cmake %ProjectDirPath% -DCMAKE_INSTALL_PREFIX=%InstallPrefix% -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=ON
cd %OldDirPath%