#include "Niflect/Test/NiflectGenerated/MyModule/MyModule0.private.h"
//#include "NiflectGenerated/SampleTest/SampleTest.private.h"

using namespace NiflectModuleReg;
using namespace Niflect;

CNiflectRegistration* TestCreateModuleReg0()
{
	CreateModuleRegistration();
	auto reg = CNiflectRegistration::StaticGet();
	reg->InitTables();
	reg->RegisterTypes();
	reg->InitTypes();
	reg->InitMethods();
	reg->InitTypesAccessorTree();
	return reg;
}
void TestDestroyModuleReg0()
{
	auto reg = CNiflectRegistration::StaticGet();
	reg->ClearTables();
	DestroyModuleRegistration();
}