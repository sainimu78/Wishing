#!/bin/bash
ProjectName=SampleProjectTemplate
BuildDirPathDebug=./DefaultBuild/Debug
BuildDirPathRelease=./DefaultBuild/Release
InstallPrefix=../Installed
Toolset="Unix Makefiles"
OldDirPath=$(pwd)

mkdir -p $BuildDirPathDebug
cd $BuildDirPathDebug
cmake ../../../../../../Project/Sample/$ProjectName -G "$Toolset" -DCMAKE_INSTALL_PREFIX="$InstallPrefix" -DPROJECT_SETUP=ON -DPROJECT_RELEASE=OFF -DCMAKE_BUILD_TYPE=Debug
cd $OldDirPath

mkdir -p $BuildDirPathRelease
cd $BuildDirPathRelease
cmake ../../../../../../Project/Sample/$ProjectName -G "$Toolset" -DCMAKE_INSTALL_PREFIX="$InstallPrefix" -DPROJECT_SETUP=ON -DPROJECT_RELEASE=OFF -DCMAKE_BUILD_TYPE=Release
cd $OldDirPath