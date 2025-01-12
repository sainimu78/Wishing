#!/bin/bash
ProjectDirPath=../../../../../../Project/Sample/SampleProject_Qt_5_8_0
BuildDirPathDebug=./DefaultBuild/Debug
BuildDirPathRelease=./DefaultBuild/Release
InstallPrefix=../Installed
Toolset="Unix Makefiles"
OldDirPath=$(pwd)

cd $BuildDirPathRelease
cmake $ProjectDirPath -G "$Toolset" -DCMAKE_INSTALL_PREFIX="$InstallPrefix" -DPROJECT_SETUP=OFF -DPROJECT_RELEASE=ON
cd $OldDirPath