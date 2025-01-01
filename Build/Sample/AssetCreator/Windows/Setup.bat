@echo off
mkdir DefaultBuild
cd DefaultBuild
cmake ..\..\..\..\..\Project\Sample\AssetCreator -DCMAKE_INSTALL_PREFIX=Installed -DPROJECT_SETUP=ON -DPROJECT_RELEASE=OFF -T v140
cd ..