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
#include "ModuleReg/Engine/Engine_private.h"
#include "Niflect/NiflectTable.h"
#include "Engine/DerivedObject.h"
#include "Niflect/Serialization/JsonFormat.h"

static Niflect::TSharedPtr<Niflect::CNiflectTable> g_defaultTable;

void TestEngineCreate()
{
	g_defaultTable = Niflect::MakeShared<Niflect::CNiflectTable>();
	Niflect::GeneratedInitialReg(g_defaultTable.Get());
	Niflect::GeneratedInitTypes();
}
void TestEngineRun()
{
	//printf("##############################\n");
	//for (uint32 idx = 0; idx < g_defaultTable->GetTypesCount(); ++idx)
	//{
	//	auto type = g_defaultTable->GetTypeByIndex(idx);
	//	printf("%s\n", type->GetTypeName().c_str());
	//}

	using CTestType = Engine::CDerivedObject;
	auto type = Niflect::StaticGetType<CTestType>();
	auto accessor = type->CreateAccessor();
	RwTree::CRwNode rw;
	CTestType srcData;
	{
		srcData.InitForTest();
		accessor->SaveToRwNode(&srcData, &rw);
	}
	auto instance = type->MakeSharedInstance<CTestType>();
	CTestType& dstData = *instance;
	accessor->LoadFromRwNode(&dstData, &rw);
	ASSERT(srcData == dstData);
	Niflect::CStringStream ss;
	RwTree::CJsonFormat::Write(&rw, ss);
	printf("%s", ss.str().c_str());
}
void TestEngineDestroy()
{
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