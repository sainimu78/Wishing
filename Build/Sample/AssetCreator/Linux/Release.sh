#!/bin/bash
ProjectName=AssetCreator
BuildDirPathDebug=./DefaultBuild/Debug
BuildDirPathRelease=./DefaultBuild/Release
InstallPrefix=../Installed
Toolset="Unix Makefiles"
OldDirPath=$(pwd)

cd $BuildDirPathRelease
cmake ../../../../../../Project/Sample/$ProjectName -G "$Toolset" -DCMAKE_INSTALL_PREFIX="$InstallPrefix" -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=ON
cd $OldDirPath