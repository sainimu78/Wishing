@echo off
cd DefaultBuild
cmake ..\..\..\..\Project\TestEditorCLI -DCMAKE_INSTALL_PREFIX=Installed -DPROJECT_SETUP=ON -DPROJECT_RELEASE=OFF
cd ..