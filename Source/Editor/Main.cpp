#include <stdio.h>
#include "Engine/Engine.h"
//#include "Windows.h"
#include "Engine/Test/TestRegistration.h"
#include "Engine/Test/TestAccessor.h"
#include "Editor/Test/TestSerializationRwTree.h"

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

	//TestAccessor::TestFieldLayout();
	TestRegistration::TestTypeNatimeta();

	//TestSerializationRwTree::TestSerialization();

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