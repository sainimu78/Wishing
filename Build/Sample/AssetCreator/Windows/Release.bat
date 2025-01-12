@echo off
set ProjectDirPath=..\..\..\..\..\Project\Sample\AssetCreator
set BuildDirPath=DefaultBuild
set InstallPrefix=Installed
set OldDirPath=%cd%

cd %BuildDirPath%
cmake %ProjectDirPath% -DCMAKE_INSTALL_PREFIX=%InstallPrefix% -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=ON -T v140
cd %OldDirPath%