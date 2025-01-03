@echo off
set ProjectName=SampleProjectTemplate
mkdir DefaultBuild
cd DefaultBuild
cmake ..\..\..\..\..\Project\Sample\%ProjectName% -DCMAKE_INSTALL_PREFIX=Installed -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=OFF
if %ERRORLEVEL% neq 0 (
    echo "### cmake generating failed ###"
    pause
)
cd ..