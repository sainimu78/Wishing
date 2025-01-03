@echo off
set ProjectDirPath=..\..\..\..\..\Project\Sample\SampleProjectTemplate
set BuildDirPath=DefaultBuild
set InstallPrefix=Installed
set OldDirPath=%cd%

mkdir %BuildDirPath%
cd %BuildDirPath%
cmake %ProjectDirPath% -DCMAKE_INSTALL_PREFIX=%InstallPrefix% -DPROJECT_SETUP=ON -DPROJECT_RELEASE=OFF
cd %OldDirPath%