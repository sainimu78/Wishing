@set old=%cd%
@cd ../../../Build/NiflectGenTool/Windows/vs2022_x64/Debug/NiflectGenTool

@NiflectGenTool ^
-n TestEngine ^
-h ../../../../../../Source/TestEngine/include/Engine/EngineObject.h ^
-h ../../../../../../Source/TestEngine/include/Engine/DerivedObject.h ^
-am ENGINE_API ^
-amh ../../../../../../Source/TestEngine/include/Engine/EngineCommon.h ^
-a ../../../../../../Source/TestEngine/include/EngineAccessorSetting.h ^
-I ../../../../../../Source/TestEngine/include ^
-I ../../../../../../Source/TestModule1/include ^
-t ../../../../../../Source/Niflect/include ^
-g ../../../../../../Generated/NiflectGenerated 

@cd %old%