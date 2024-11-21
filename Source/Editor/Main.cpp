#include <stdio.h>
#include "Engine/Engine.h"

//#include "Windows.h"

#include "Engine/Test/TestRegistration.h"
#include "Engine/Test/TestAccessor.h"
#include "Editor/Test/TestSerializationRwTree.h"
#include "TestModule0/TestModule0.h"
#include "Niflect/NiflectRegistration.h"
#include "Niflect/Memory/Default/DefaultMemory.h"
#include "Engine/Test/TestAccessor2.h"
#include "Engine/Engine.h"
//#include "Engine/DerivedObject.h"
//#include "Niflect/Serialization/JsonFormat.h"

class CMyClassForSimplifiedMakeShared
{
public:
	CMyClassForSimplifiedMakeShared()
		: m_float(1.23f)
		, m_bool(true)
		, m_double(43.21)
		, m_arr{}
	{

	}
	float m_float;
	bool m_bool;
	double m_double;
	int m_arr[128];
};

typedef void (*FuncTestAPI_C)();

int main(int argc, char** argv)
{
	TestAPI_Cpp();


	//TestSerializationRwTree::TestMemory();

	//TestAccessor::TestFieldLayout();
	
	//TestRegistration::TestTypeNatimeta();

	//TestModule0::LoadTypes();
	//TestModule0::UnloadTypes();

	TestSerializationRwTree::TestSerialization();


	//auto memTest = Niflect::GetDefaultMemoryStats();
	//TestEngineCreate();
	////begin, 如须测试, Editor cmake未接入生成代码的头文件搜索路径时, 应将Engine的相应路径改为PUBLIC
	////auto a = Niflect::StaticGetType<Engine::CDerivedObject>();
	////auto b = a->MakeSharedInstance<Engine::CDerivedObject>();
	////b->InitForTest();
	////RwTree::CRwNode rw;
	////a->SaveInstanceToRwNode(b.Get(), &rw);
	////Niflect::CStringStream ss;
	////RwTree::CJsonFormat::Write(&rw, ss);
	////printf("%s\n", ss.str().c_str());
	////end
	//TestEngineRun();
	//TestEngineDestroy();


	//TestAccessor2::TestFieldLayout();


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