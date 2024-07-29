#include <stdio.h>
#include "Engine/Engine.h"
//#include "Windows.h"
#include "Niflect/Memory/DefaultMemory.h"
#include "Niflect/Memory/Scope/PooledMemoryScope.h"
#include "Niflect/Base/NiflectBase.h"
#include "Niflect/Memory/Stats/NiflectMemoryStats.h"

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
	
	using namespace Niflect;
	{
		auto stats = DebugGetMemoryStats();
		{
			auto a = MakeShared<CMyClassForSimplifiedMakeShared>();
		}
		{
			CPooledMemoryScope scope;
			auto a = MakeShared<CMyClassForSimplifiedMakeShared>();
		}
		printf("");
	}
	auto mem = Niflect::CMemory::Alloc(10);
	Niflect::CMemory::Free(mem);

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