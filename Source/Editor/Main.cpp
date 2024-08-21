#include <stdio.h>
#include "Engine/Engine.h"

//#include "Windows.h"

#include "Engine/Test/TestRegistration.h"
#include "Engine/Test/TestAccessor.h"
#include "Editor/Test/TestSerializationRwTree.h"
#include "TestModule0/TestModule0.h"
#include "Niflect/NiflectRegistration.h"

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

	//TestSerializationRwTree::TestMemory();

	//TestAccessor::TestFieldLayout();
	
	TestRegistration::TestTypeNatimeta();

	//TestModule0::LoadTypes();
	//TestModule0::UnloadTypes();

	//TestSerializationRwTree::TestSerialization();

	//{
	//	auto hLib = LoadLibrary("Engine");
	//	if (hLib != NULL)
	//	{
	//		if (auto Func = reinterpret_cast<FuncGeneratedNiflectRegistrationGet>(GetProcAddress(hLib, "GeneratedNiflectRegistrationGet")))
	//			Func();
	//	}
	//}
	//{
	//	auto hLib = LoadLibrary("TestModule0");
	//	if (hLib != NULL)
	//	{
	//		if (auto Func = reinterpret_cast<FuncGeneratedNiflectRegistrationGet>(GetProcAddress(hLib, "GeneratedNiflectRegistrationGet")))
	//			Func();
	//		if (auto Func = reinterpret_cast<FuncGeneratedNiflectRegistrationRelease>(GetProcAddress(hLib, "GeneratedNiflectRegistrationRelease")))
	//			Func();
	//		FreeLibrary(hLib);
	//	}
	//}

	printf("Finished\n");
	fflush(stdout);
	return 0;
}