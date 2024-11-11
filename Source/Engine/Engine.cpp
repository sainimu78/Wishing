#include "Engine/Engine.h"
#include <stdio.h>

void TestAPI_Cpp()
{
	printf("Invoke C++ API\n");
	fflush(stdout);
}
void TestAPI_C()
{
	printf("Invoke C API\n");
	fflush(stdout);
}

#ifdef ENABLED_TEST_MODULEREG_GEN_BY_NGT
#include "Engine/ModuleReg/Engine_private.h"
#include "Niflect/NiflectTable.h"
#include "Engine/DerivedObject.h"
#include "Niflect/Serialization/JsonFormat.h"
#include "TestModule1/TestModule1.h"

static Niflect::TSharedPtr<Niflect::CNiflectTable> g_defaultTable;

void TestEngineCreate()
{
	TestModule1Create();

	g_defaultTable = Niflect::MakeShared<Niflect::CNiflectTable>();
	Niflect::GeneratedInitialReg(g_defaultTable.Get());
	Niflect::GeneratedInitTypes();
	g_defaultTable->InitTypesLayout();
}
void TestEngineRun()
{
	{
		using CTestType = Engine::CDerivedFromModule1;
		auto type = Niflect::StaticGetType<CTestType>();
		RwTree::CRwNode rw;
		CTestType srcData;
		{
			srcData.InitForTest();
			type->SaveInstanceToRwNode(&srcData, &rw);
		}
		auto instance = type->MakeSharedInstance<CTestType>();
		CTestType& dstData = *instance;
		type->LoadInstanceFromRwNode(&dstData, &rw);
		ASSERT(srcData == dstData);
		Niflect::CStringStream ss;
		RwTree::CJsonFormat::Write(&rw, ss);
		printf("%s", ss.str().c_str());
	}
	{
		using CTestType = Engine::CDerivedObject;
		auto type = Niflect::StaticGetType<CTestType>();
		RwTree::CRwNode rw;
		CTestType srcData;
		{
			srcData.InitForTest();
			type->SaveInstanceToRwNode(&srcData, &rw);
		}
		auto instance = type->MakeSharedInstance<CTestType>();
		CTestType& dstData = *instance;
		type->LoadInstanceFromRwNode(&dstData, &rw);
		ASSERT(srcData == dstData);
		Niflect::CStringStream ss;
		RwTree::CJsonFormat::Write(&rw, ss);
		printf("%s", ss.str().c_str());
	}
}
void TestEngineDestroy()
{
	TestModule1Destroy();
	g_defaultTable = NULL;
}
#else
void TestEngineCreate()
{
}
void TestEngineRun()
{
}
void TestEngineDestroy()
{
}
#endif