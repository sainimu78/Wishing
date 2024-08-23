#include <stdio.h>
#include "NiflectGen/Test/TestParseCpp.h"
#include "NiflectGen/Generator/Generator.h"
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Util/DebugUtil.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Memory/Default/DefaultMemory.h"

int main()
{
	//Test0();
	// 
	//TestParseCpp(
	//	"E:/S3/S3ResourceEditor/engine_ref/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Test/TestTypeBindingSetting.cpp",
	//	"E:/S3/S3ResourceEditor/engine_ref/SampleTest/SampleGamePrototyping/Cos/Client"
	//);

	//std::vector<std::string> vecInclude;
	//vecInclude.push_back("E:/S3/S3ResourceEditor/engine_ref/S3Engine");
	//vecInclude.push_back("E:/S3/S3ResourceEditor/engine_ref/SampleTest/SampleGamePrototyping/Cos/Client");
	//vecInclude.push_back("E:/S3/S3ResourceEditor/engine_ref/Generated");
	//TestParseCpp(vecInclude, "E:/S3/S3ResourceEditor/engine_ref/Generated/NiflectGenerated/SampleTest/TempSource.cpp");

	//std::vector<std::string> vecInclude;
	//vecInclude.push_back("E:/S3/S3ResourceEditor/engine_ref/S3Engine");
	//vecInclude.push_back("E:/S3/S3ResourceEditor/engine_ref/SampleTest/SampleGamePrototyping/Cos/Client");
	//vecInclude.push_back("E:/S3/S3ResourceEditor/engine_ref/Generated");
	//TestParseCpp(vecInclude, "E:/S3/S3ResourceEditor/engine_ref/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Test//TestTypeBindingSetting.cpp");

	//using namespace NiflectGen;
	//InitTypeBindingTable();

	using namespace NiflectGen;

	using namespace Niflect;
	//auto table = CreateTypeBindingTable();
	auto memTest = GetDefaultMemoryStats();
	{
		auto gen = CreateGenerator();
		//if (false)
		//{
		//	gen->AddTypeBindingSettingHeader(CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Niflect/Test/TestTypeBindingSetting.h"));
		//	gen->AddFileForSearching(CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Niflect/Test/TestTypesHeaderForGen0.h"));
		//	gen->AddFileForSearching(CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Niflect/Test/TestTypesHeaderForGen1.h"));
		//	gen->AddFileForSearching(CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Niflect/Test/TestTypesHeaderForGen2.h"));
		//	gen->AddIncludePath(NiflectGenDefinition::Path::BypassingSTL);
		//	for (auto& it : NiflectGenDefinition::Path::CLangParserArgs_I)
		//		gen->AddIncludePath(it);
		//	gen->ParseSourceFiles();
		//}
		//if (false)
		//{
		//	gen->AddTypeBindingSettingHeader(CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Niflect/Test/TestMyGlobalBindingSetting.h"));
		//	gen->AddFileForSearching(CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Niflect/Test/MyClassForGen.h"));
		//	gen->AddIncludePath(NiflectGenDefinition::Path::BypassingSTL);
		//	for (auto& it : NiflectGenDefinition::Path::CLangParserArgs_I)
		//		gen->AddIncludePath(it);
		//	gen->ParseSourceFiles();
		//}
		if (true)
		{
			CModuleRegInfo info;
			info.m_moduleName = "Engine";
			info.m_genIncludeBasePath = "NiflectGenerated";
			info.m_genBasePath = "F:/Fts/Proj/Test/Interedit/Generated";
			//begin, 指定需要解析的头文件列表
			info.m_vecOriginalHeader.push_back("F:/Fts/Proj/Test/Interedit/Source/Engine/EngineObject.h");
			info.m_vecOriginalHeader.push_back("F:/Fts/Proj/Test/Interedit/Source/Engine/Asset.h");
			//end
			//begin, 指定BindingSetting头文件列表
			info.m_vecBindingSettingHeader.push_back("F:/Fts/Proj/Test/Interedit/Source/Engine/EngineTypeBindingSetting.h");
			//end
			constexpr const char* CLangParserArgs_I[] = {
				//begin, 解析的头文件源码搜索目录
				"F:/Fts/Proj/Test/Interedit/Source",
				//end
				//begin, 用于旁路clang_parseTranslationUnit过程中STL头文件解析, 可大幅减少耗时
				//todo: 旁路代码极简单, 可只在内存中生成
				"F:/Fts/Proj/Test/Interedit/Source/BypassCode/NiflectSTL",
				//end
			};
			for (auto& it : CLangParserArgs_I)
				info.m_vecHeaderSearchPath.push_back(it);
			gen->SetModuleRegInfo(info);
			gen->Generate();
			gen->Save();
		}
	}

	return 0;
}