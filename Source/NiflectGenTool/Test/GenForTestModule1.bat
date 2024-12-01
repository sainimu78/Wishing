@set old=%cd%
@cd ../../../Build/NiflectGenTool/Windows/vs2022_x64/Debug/NiflectGenTool

@NiflectGenTool ^
-n TestModule1 ^
-h ../../../../../../Source/TestModule1/include/TestModule1/TestClass1.h ^
-am TESTMODULE1_API ^
-amh ../../../../../../Source/TestModule1/include/TestModule1Common.h ^
-a ../../../../../../Source/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h ^
-I ../../../../../../Source/TestModule1/include ^
-I ../../../../../../Source/Niflect/include ^
-g ../../../../../../Generated/NiflectGenerated 

@cd %old%