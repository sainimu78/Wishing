#include <stdio.h>
#include "Engine/Engine.h"
//#include "Windows.h"
#include "Niflect/Memory/Default/DefaultMemory.h"
#include "Niflect/Memory/Default/DefaultMemoryPoolScope.h"
#include "Niflect/Base/NiflectBase.h"
#include "Niflect/Memory/Stats/NiflectMemoryStats.h"
#include "Niflect/Serialization/RwTree.h"
#include "Niflect/Util/DebugUtil.h"
#include "Niflect/Serialization/JsonFormat.h"
#include "Niflect/Serialization/BinaryFormat.h"
#include <fstream>
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Test/TestDefinition.h"

class CMyClassForSimplifiedMakeShared
{
public:
	CMyClassForSimplifiedMakeShared()
		: m_float(1.23f)
		, m_bool(true)
		, m_double(43.21)
	{

	}
	float m_float;
	bool m_bool;
	double m_double;
};

typedef void (*FuncTestAPI_C)();

int main(int argc, char** argv)
{
	TestAPI_Cpp();
	
	{
		using namespace Niflect;
		CDefaultMemoryStatsScope memTestScope;
		auto stats = GetDefaultMemoryStats();
		if (false)//TLS Default Allocator
		{
			CDefaultMemoryPoolScope sdddddd;

			TestMemoryStatsOnThreadsBegin();
			DebugPrintTestTree();
			TestMemoryStatsOnThreadsEnd();
		}
		if (false)//JSON 格式序列化
		{
			CRwNode root;
			std::ifstream ifs(TestDefinition::FilePath::InputJson_AnimGraphEditorData, std::ios::binary);
			CJsonFormat::Read(&root, ifs);

			std::ofstream ofs(TestDefinition::FilePath::OutputJson_AnimGraphEditorData, std::ios::binary);
			CJsonFormat::Write(&root, ofs);
		}
		if (true)//JSON & 自定义 Binary 格式相互转换
		{
			{
				CRwNode root;
				DebugBuildStructure(&root);
				{
					std::ofstream ofs(TestDefinition::FilePath::OutputBinary_0, std::ios::binary);
					CBinaryFormat::A_2(&root, ofs);
				}
				{
					std::ofstream ofs(TestDefinition::FilePath::OutputJson_0, std::ios::binary);
					CJsonFormat::Write(&root, ofs);
				}
			}
			{
				CRwNode root;
				std::ifstream ifs(TestDefinition::FilePath::OutputBinary_0, std::ios::binary);
				CBinaryFormat::B_2(&root, ifs);

				std::ofstream ofs(TestDefinition::FilePath::OutputJson_1, std::ios::binary);
				CJsonFormat::Write(&root, ofs);
			}

			ASSERT(NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::OutputJson_0) == NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::OutputJson_1));
		}
	}

	//auto hLib = LoadLibrary("Engine.dll");
	//if (hLib != NULL)
	//{
	//	if (auto Func = reinterpret_cast<FuncTestAPI_C>(GetProcAddress(hLib, "TestAPI_C")))
	//		Func();
	//}

	printf("Finished\n");
	fflush(stdout);
	return 0;
}