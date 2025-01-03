@echo off
set ProjectName=AssetCreator
mkdir DefaultBuild
cd DefaultBuild
cmake ..\..\..\..\..\Project\Sample\%ProjectName% -DCMAKE_INSTALL_PREFIX=Installed -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=OFF -T v140
if %ERRORLEVEL% neq 0 (
    echo "### cmake generating failed ###"
    pause
)
cd ..