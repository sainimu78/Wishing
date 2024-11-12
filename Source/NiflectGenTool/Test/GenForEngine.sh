#!/bin/bash

old=$(pwd)
cd ../../../Build/NiflectGenTool/Linux/Linux_NiflectGenTool_x64/Debug/NiflectGenTool

./NiflectGenTool \
-n Engine \
-h /home/sainimu78/Fts/Interedit/Source/Engine/EngineObject.h \
-h /home/sainimu78/Fts/Interedit/Source/Engine/DerivedObject.h \
-am ENGINE_API \
-amh /home/sainimu78/Fts/Interedit/Source/Engine/EngineCommon.h \
-a /home/sainimu78/Fts/Interedit/Source/Engine/EngineAccessorSetting.h \
-I /home/sainimu78/Fts/Interedit/Source \
-p /home/sainimu78/Fts/Interedit/Generated/NiflectGenerated \
-fs

cd $old
