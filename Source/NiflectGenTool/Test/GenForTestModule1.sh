#!/bin/bash

old=$(pwd)
cd ../../../Build/NiflectGenTool/Linux/Make_x64/Debug/NiflectGenTool

./NiflectGenTool \
-n TestModule1 \
-h ../../../../../../Source/TestModule1/TestClass1.h \
-am TESTMODULE1_API \
-amh ../../../../../../Source/TestModule1/TestModule1Common.h \
-a ../../../../../../Source/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h \
-I ../../../../../../Source \
-I ../../../../../../Source/Niflect/include \
-g ../../../../../../Generated/NiflectGenerated 

cd $old
