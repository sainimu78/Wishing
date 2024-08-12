#!/bin/bash

BuildPath=$(pwd)
cd ../../../../Build/Interedit/Windows/vs2022_Interedit_x64/Editor/
"$BuildPath/MinGW_Interedit_x64/Debug/Interedit/Debug/Editor"
cd "$BuildPath"
