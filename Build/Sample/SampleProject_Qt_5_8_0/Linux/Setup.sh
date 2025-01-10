#!/bin/bash
ProjectDirPath=../../../../../../Project/Sample/SampleProject_Qt_5_8_0
BuildDirPathDebug=./DefaultBuild/Debug
BuildDirPathRelease=./DefaultBuild/Release
InstallPrefix=../Installed
Toolset="Unix Makefiles"
OldDirPath=$(pwd)

mkdir -p $BuildDirPathRelease
cd $BuildDirPathRelease
cmake $ProjectDirPath -G "$Toolset" -DCMAKE_INSTALL_PREFIX="$InstallPrefix" -DPROJECT_SETUP=ON -DPROJECT_RELEASE=OFF -DCMAKE_BUILD_TYPE=Release
cd $OldDirPath