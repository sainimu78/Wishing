@set old=%cd%
@cd ../../../Build/NiflectGenTool/Windows/vs2022_x64/Debug/NiflectGenTool

@NiflectGenTool ^
-n Engine ^
-h ../../../../../../Source/Engine/include/Engine/EngineObject.h ^
-h ../../../../../../Source/Engine/include/Engine/DerivedObject.h ^
-am ENGINE_API ^
-amh ../../../../../../Source/Engine/include/Engine/EngineCommon.h ^
-a ../../../../../../Source/Engine/include/EngineAccessorSetting.h ^
-I ../../../../../../Source/Engine/include ^
-I ../../../../../../Source/TestModule1/include ^
-t ../../../../../../Source/Niflect/include ^
-g ../../../../../../Generated/NiflectGenerated 

@cd %old%