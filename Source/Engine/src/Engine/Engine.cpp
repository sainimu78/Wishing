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
#include "Engine_private.h"
#include "Niflect/NiflectTable.h"
#include "Engine/DerivedObject.h"
#include "Niflect/Serialization/JsonFormat.h"
#include "TestModule1/TestModule1.h"
#include "Niflect/NiflectModule.h"
#ifdef WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

Niflect::TSharedPtr<Niflect::CNiflectTable> g_defaultTable;

void TestEngineCreate()
{
	Niflect::CNiflectModuleManager mgr;
	mgr.RegisterStaticlyLoadedModule("TestModule1");
	ASSERT(mgr.GetModulesCount() == 1);
	printf("Found %u module%s:\n", mgr.GetModulesCount(), mgr.GetModulesCount()>1?"s":"");
	for (uint32 idx = 0; idx < mgr.GetModulesCount(); ++idx)
	{
		auto& it = mgr.GetModule(idx);
		printf("[%u] %s\n", idx, it.m_info->GetName().c_str());
	}

	TestModule1Create();

	g_defaultTable = Niflect::MakeShared<Niflect::CNiflectTable>();
	Niflect::GeneratedInitialReg(g_defaultTable.Get());
	Niflect::GeneratedInitTypes();
	g_defaultTable->InitTypesLayout();
}
void TestEngineRun()
{
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
		printf("%s\n", ss.str().c_str());
	}
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
		printf("%s\n", ss.str().c_str());
	}
	{
		auto type = Niflect::CEnum::Cast(Niflect::StaticGetType<TestModule1::ETestEnum0>());
		auto& em = type->GetEnumMeta();
		for (auto& it : em.m_vecEnumConstMeta)
		{
			Niflect::CString name = it.m_name;
			if (auto nata = it.GetNata())
			{
				auto ecn = TestModule1::CMyEnumConstNata::Cast(nata);
				name = ecn->m_friendlyName;
			}
			printf("%s\n", name.c_str());
		}
		printf("");
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