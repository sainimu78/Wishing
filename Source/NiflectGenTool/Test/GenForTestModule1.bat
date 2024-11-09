@set old=%cd%
@cd ../../../Build/NiflectGenTool/Windows/vs2022_NiflectGenTool_x64/Debug/NiflectGenTool

@NiflectGenTool ^
-n TestModule1 ^
-h F:/Fts/Proj/Test/Interedit/Source/TestModule1/TestClass1.h ^
-am TESTMODULE1_API ^
-amh F:/Fts/Proj/Test/Interedit/Source/TestModule1/TestModule1Common.h ^
-a F:/Fts/Proj/Test/Interedit/Source/Niflect/CommonlyUsed/DefaultAccessorSetting.h ^
-I F:/Fts/Proj/Test/Interedit/Source ^
-p F:/Fts/Proj/Test/Interedit/Generated/NiflectGenerated 

@cd %old%