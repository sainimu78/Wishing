@echo off
set ProjectDirPath=..\..\..\..\..\Project\Sample\SampleProject_Qt_6_8_1
set BuildDirPath=DefaultBuild
set InstallPrefix=Installed
set OldDirPath=%cd%

cd %BuildDirPath%
::-T v140 is required for Qt 5.8.0
cmake %ProjectDirPath% -DCMAKE_INSTALL_PREFIX=%InstallPrefix% -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=ON
cd %OldDirPath%