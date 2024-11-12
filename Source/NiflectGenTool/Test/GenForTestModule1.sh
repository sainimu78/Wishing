#!/bin/bash

old=$(pwd)
cd ../../../Build/NiflectGenTool/Linux/Make_x64/Debug/NiflectGenTool

./NiflectGenTool \
-n TestModule1 \
-h /home/sainimu78/Fts/Interedit/Source/TestModule1/TestClass1.h \
-am TESTMODULE1_API \
-amh /home/sainimu78/Fts/Interedit/Source/TestModule1/TestModule1Common.h \
-a /home/sainimu78/Fts/Interedit/Source/Niflect/CommonlyUsed/DefaultAccessorSetting.h \
-I /home/sainimu78/Fts/Interedit/Source \
-p /home/sainimu78/Fts/Interedit/Generated/NiflectGenerated 

cd $old
