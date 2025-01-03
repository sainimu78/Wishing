@echo off
set ProjectName=AssetCreator
cd DefaultBuild
cmake ..\..\..\..\..\Project\Sample\%ProjectName% -DCMAKE_INSTALL_PREFIX=Installed -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=ON -T v140
cd ..