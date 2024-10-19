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
#include "ModuleReg/Engine/Engine.private.h"
#include "BuiltinAccessor.h"
#include "Engine/EngineObject.h"
#include "Engine/Asset.h"
#include "Niflect/Serialization/RwTree.h"
#include "Niflect/Serialization/JsonFormat.h"

////begin, 已验证无法通过特化区分原始类型与别名(using和typedef定义的别名)
////using Nihao = float;
////typedef float SSSSS;
//namespace Niflect
//{
//	template <>
//	CNiflectType* StaticGetType<Nihao>()
//	{
//		return TInternalRegisteredType<Nihao>::s_type;
//	}
//	template <>
//	bool __InternalStaticIsValid<Nihao>()
//	{
//		return TInternalRegisteredType<Nihao>::s_type != NULL;
//	}
//	template <>
//	CNiflectType* StaticGetType<SSSSS>()
//	{
//		return TInternalRegisteredType<SSSSS>::s_type;
//	}
//	template <>
//	bool __InternalStaticIsValid<SSSSS>()
//	{
//		return TInternalRegisteredType<SSSSS>::s_type != NULL;
//	}
//}
////end

void TestEngineCreate()
{
	{
		//模拟的 Static Reg
		auto reg = Niflect::CNiflectRegistration::GetMutable();
		auto table = reg->GetMutableMiscTable();
		//现未实现支持直接生成无标签BindingType的TypeReg, 因此在模拟的 Static Reg 阶段中注册
		//为无标签的BindingType办法为: 区分BindingType, 如为BuiltIn类型, 则生成绑定默认FieldLayout创建函数的TypeReg
		//另一种思路是支持别名加标签, 这要求在BindingSetting中的BindingType也使用别名, 但不建议这样使用, 因为对别名加标签可能是希望专门为被加标签的别名注册一种类型
		table->RegisterType<Niflect::CNiflectType, float>("float", &Niflect::__InternalCreateFieldLayoutForFunctionPointer<Engine::CFloatAccessor>);
		table->RegisterType<Niflect::CNiflectType, bool>("bool", &Niflect::__InternalCreateFieldLayoutForFunctionPointer<Engine::CBoolAccessor>);

		////begin, 已验证无法通过特化区分原始类型与别名(using和typedef定义的别名)
		//table->RegisterType<Niflect::CNiflectType, Nihao>("Nihao", &Niflect::__InternalCreateFieldLayoutForFunctionPointer<Engine::CFloatAccessor>);
		//table->RegisterType<Niflect::CNiflectType, SSSSS>("SSSSS", &Niflect::__InternalCreateFieldLayoutForFunctionPointer<Engine::CFloatAccessor>);
		////end
	}
	{
		//Initial Reg
		GeneratedNiflectRegistrationInitialReg();
		GeneratedNiflectRegistrationInitTypes();
	}
}
void TestEngineDestroy()
{
	GeneratedNiflectRegistrationRelease();
}
void TestEngineRun()
{
	Niflect::TArrayNif<Niflect::CNiflectType*> vec;
	vec.push_back(Niflect::StaticGetType<float>());
	vec.push_back(Niflect::StaticGetType<bool>());
	vec.push_back(Niflect::StaticGetType<Engine::CEngineObject>());
	vec.push_back(Niflect::StaticGetType<Engine::CAsset>());
	for (auto& it : vec)
		printf("%s, ", it->GetTypeName().c_str());
	printf("\n");

	{
		for (auto& type : vec)
		{
			using namespace RwTree;
			using namespace Niflect;
			auto sharedSrcData = type->MakeSharedInstance<void*>();
			auto layout = type->CreateFieldLayout();
			if (type == Niflect::StaticGetType<float>())
			{
				auto& srcData = *reinterpret_cast<float*>(sharedSrcData.Get());
				srcData = 12.3f;
			}
			else if (type == Niflect::StaticGetType<bool>())
			{
				auto& srcData = *reinterpret_cast<bool*>(sharedSrcData.Get());
				srcData = true;
			}
			else if (type == Niflect::StaticGetType<Engine::CEngineObject>())
			{
				auto& srcData = *reinterpret_cast<Engine::CEngineObject*>(sharedSrcData.Get());
				srcData.InitForTest();
			}
			else if (type == Niflect::StaticGetType<Engine::CAsset>())
			{
				auto& srcData = *reinterpret_cast<Engine::CAsset*>(sharedSrcData.Get());
				srcData.InitForTest();
			}
			else
			{
				ASSERT(false);
			}

			CRwNode rw;
			layout->SaveToRwNode(sharedSrcData.Get(), &rw);
			CStringStream ss;
			CJsonFormat::Write(&rw, ss);

			auto sharedDstData = type->MakeSharedInstance<void*>();
			layout->LoadFromRwNode(sharedDstData.Get(), &rw);

			if (type == Niflect::StaticGetType<float>())
			{
				auto& srcData = *reinterpret_cast<float*>(sharedSrcData.Get());
				auto& dstData = *reinterpret_cast<float*>(sharedDstData.Get());
				ASSERT(srcData == dstData);
			}
			else if (type == Niflect::StaticGetType<bool>())
			{
				auto& srcData = *reinterpret_cast<bool*>(sharedSrcData.Get());
				auto& dstData = *reinterpret_cast<bool*>(sharedDstData.Get());
				ASSERT(srcData == dstData);
			}
			else if (type == Niflect::StaticGetType<Engine::CEngineObject>())
			{
				auto& srcData = *reinterpret_cast<Engine::CEngineObject*>(sharedSrcData.Get());
				auto& dstData = *reinterpret_cast<Engine::CEngineObject*>(sharedDstData.Get());
				ASSERT(srcData == dstData);
			}
			else if (type == Niflect::StaticGetType<Engine::CAsset>())
			{
				auto& srcData = *reinterpret_cast<Engine::CAsset*>(sharedSrcData.Get());
				auto& dstData = *reinterpret_cast<Engine::CAsset*>(sharedDstData.Get());
				ASSERT(srcData == dstData);
			}
		}
	}

	////begin, 已验证无法通过特化区分原始类型与别名(using和typedef定义的别名)
	//auto d = Niflect::StaticGetType<Nihao>();
	//auto e = Niflect::StaticGetType<SSSSS>();
	//printf("");
	////end

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
#else
#include "Niflect/NiflectRegistration.h"
Niflect::CNiflectRegistration* GeneratedNiflectRegistrationGet()
{
	return NULL;
}
void GeneratedNiflectRegistrationInitialReg()
{
}
void GeneratedNiflectRegistrationInitTypes()
{
}
#endif