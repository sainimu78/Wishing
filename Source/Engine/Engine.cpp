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

#include "ModuleReg/Engine/Engine_private.h"
#include "Niflect/NiflectTable.h"
#include "NiflectGen/Test/TestOriginalCodeGen0.h"
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

	auto type = Niflect::StaticGetType<TestMyFinding::CMyClass_0>();
	auto accessor = type->CreateAccessor();
	RwTree::CRwNode rw;
	auto instance = type->MakeSharedInstance<void*>();
	accessor->SaveToRwNode(instance.Get(), &rw);
	Niflect::CStringStream ss;
	RwTree::CJsonFormat::Write(&rw, ss);
	printf("%s", ss.str().c_str());
}
void TestEngineDestroy()
{
	g_defaultTable = NULL;
}