@echo off
set ProjectName=AssetCreator
mkdir DefaultBuild
cd DefaultBuild
cmake ..\..\..\..\..\Project\Sample\%ProjectName% -DCMAKE_INSTALL_PREFIX=Installed -DPROJECT_SETUP=ON -DPROJECT_RELEASE=OFF -T v140
cd ..