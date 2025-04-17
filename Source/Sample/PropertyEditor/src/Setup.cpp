#include "Setup.h"
#include "PropertyEditor_private.h"

Niflect::CNiflectTable* Setup()
{
	auto reg = Niflect::GetModuleRegistry();
	reg->InitRegisteredModules();

	ASSERT(reg->GetModulesCount() == 1);
	auto mod = reg->GetModuleByIndex(0);
	return mod->GetTable();
}