#!/bin/bash

old=$(pwd)
cd ../../../Build/NiflectGenTool/Linux/Make_x64/Debug/NiflectGenTool

./NiflectGenTool \
-n Engine \
-h ../../../../../../Source/Engine/EngineObject.h \
-h ../../../../../../Source/Engine/DerivedObject.h \
-am ENGINE_API \
-amh ../../../../../../Source/Engine/EngineCommon.h \
-a ../../../../../../Source/Engine/EngineAccessorSetting.h \
-I ../../../../../../Source/Engine/include \
-I ../../../../../../Source/TestModule1/include \
-t ../../../../../../Source/Niflect/include \
-g ../../../../../../Generated/NiflectGenerated 

cd $old
