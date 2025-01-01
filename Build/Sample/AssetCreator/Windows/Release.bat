@echo off
cd DefaultBuild
cmake ..\..\..\..\..\Project\Sample\AssetCreator -DCMAKE_INSTALL_PREFIX=Installed -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=ON -T v140
cd ..