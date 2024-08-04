#include <stdio.h>
#include "Engine/Engine.h"
#include "Engine/Engine.private.h"

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