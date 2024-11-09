#include "TestModule1/TestModule1.h"
#include "TestModule1/ModuleReg/TestModule1_private.h"
#include "Niflect/NiflectTable.h"

using namespace Niflect;

static Niflect::TSharedPtr<CNiflectTable> g_defaultTable;

void TestModule1Create()
{
	g_defaultTable = Niflect::MakeShared<CNiflectTable>();
	GeneratedInitialReg(g_defaultTable.Get());
	GeneratedInitTypes();
	g_defaultTable->InitTypesLayout();
}
void TestModule1Destroy()
{
	g_defaultTable = NULL;
}