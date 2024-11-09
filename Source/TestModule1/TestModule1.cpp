#include "TestModule1/TestModule1.h"
#include "TestModule1/ModuleReg/TestModule1_private.h"

namespace TestModule1
{
	using namespace Niflect;

	static Niflect::TSharedPtr<Niflect::CNiflectTable> g_defaultTable;

	void TestModule1Create()
	{
		g_defaultTable = Niflect::MakeShared<Niflect::CNiflectTable>();
		Niflect::GeneratedInitialReg(g_defaultTable.Get());
		Niflect::GeneratedInitTypes();
		g_defaultTable->InitTypesLayout();
	}
	void TestModule1Destroy()
	{
		g_defaultTable = NULL;
	}
}