@echo off
mkdir DefaultBuild
cd DefaultBuild
cmake ..\..\..\..\Project\TestEditorCLI -DCMAKE_INSTALL_PREFIX=Installed -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=ON
cd ..