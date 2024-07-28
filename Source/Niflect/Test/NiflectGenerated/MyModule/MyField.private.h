#pragma once
#include "Niflect/Type/NiflectTable.h"
#include "Niflect/Test/MyField.h"

namespace MyTestClassScope
{
	using namespace Niflect;

	class CInheritableTypeReg_CFloatField
	{
	public:
		static void StaticRegisterType(CNiflectTable& table)
		{
			table.RegisterType<CClass, CFloatField>("CFloatField", &StaticCreateFieldLayout, typeid(float).hash_code());
		}
		static void StaticInitInheritance()
		{
		}
		static CSharedField StaticCreateFieldLayout()
		{
			auto shared0 = CreateField<CFloatField, CFloatField>();
			auto field0 = shared0.Get();
			return shared0;
		}
	};
	class CInheritableTypeReg_CStringField
	{
	public:
		static void StaticRegisterType(CNiflectTable& table)
		{
			table.RegisterType<CClass, CStringField>("CStringField", &StaticCreateFieldLayout, typeid(CString).hash_code());
		}
		static void StaticInitInheritance()
		{
		}
		static CSharedField StaticCreateFieldLayout()
		{
			auto shared0 = CreateField<CStringField, CStringField>();
			auto field0 = shared0.Get();
			return shared0;
		}
	};
	class CInheritableTypeReg_CBoolField
	{
	public:
		static void StaticRegisterType(CNiflectTable& table)
		{
			table.RegisterType<CClass, CBoolField>("CBoolField", &StaticCreateFieldLayout, typeid(bool).hash_code());
		}
		static void StaticInitInheritance()
		{
		}
		static CSharedField StaticCreateFieldLayout()
		{
			auto shared0 = CreateField<CBoolField, CBoolField>();
			auto field0 = shared0.Get();
			return shared0;
		}
	};
}