#include "Engine/Engine.h"
#include <stdio.h>
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

//todo: 2024.08.11, 计划改为
//手工注册的静态反射宏称作 Static Reg
//生成的注册代码称作 Initial Reg
//其它阶段注册称作 Dynamic Reg
//
//在 Initial Reg 之后才能进行 CreateFieldLayout
//这意味着之前阶段的注册信息无任何依赖, 只需要注册类型本身即可

//using namespace NiflectModuleReg;
//using namespace Niflect;

//CNiflectRegistration* TestCreateModuleReg0()
//{
//	//CreateModuleRegistration();
//	auto reg = CNiflectRegistration::Get();
//	reg->InitTables();
//	reg->RegisterTypes();
//	reg->InitTypes();
//	reg->InitMethods();
//	reg->InitTypesAccessorTree();
//	return reg;
//}
//void TestDestroyModuleReg0()
//{
//	auto reg = CNiflectRegistration::Get();
//	reg->ClearTables();
//	CNiflectRegistration::StaticRelease();
//	//DestroyModuleRegistration();
//}