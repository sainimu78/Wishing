@echo off
set ProjectName=SampleProjectTemplate
mkdir DefaultBuild
cd DefaultBuild
cmake ..\..\..\..\..\Project\Sample\%ProjectName% -DCMAKE_INSTALL_PREFIX=Installed -DPROJECT_SETUP=ON -DPROJECT_RELEASE=OFF
cd ..