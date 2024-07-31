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
#include <fstream>

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
		if (false)//TLS Default Allocator ≤‚ ‘
		{
			CDefaultMemoryPoolScope sdddddd;

			TestMemoryStatsOnThreadsBegin();
			DebugPrintTestTree();
			TestMemoryStatsOnThreadsEnd();
		}
		if (true)
		{
#define CONCAT_CONST_CHAR_2(a, b) a"" b
#define CONCAT_CONST_CHAR_3(a, b, c) CONCAT_CONST_CHAR_2(a, b)"" c
#define CONCAT_CONST_CHAR_4(a, b, c, d) CONCAT_CONST_CHAR_3(a, b, c)"" d
#define ROOT_TEST_PATH "../../../../../Source/Niflect/Test"
			const char* fileInput = CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/RwTree/Input/mhlike.animgraph.meta");
			const char* fileOutput = CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/RwTree/Output/mhlike.animgraph.meta");

			CRwNode root;
			std::ifstream ifs(fileInput, std::ios::binary);
			CJsonFormat::Read(&root, ifs);

			std::ofstream ofs(fileOutput, std::ios::binary);
			CJsonFormat::Write(&root, ofs);
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