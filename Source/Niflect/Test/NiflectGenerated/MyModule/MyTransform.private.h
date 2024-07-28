#pragma once
#include "Niflect/Type/NiflectTable.h"
#include "Niflect/Test/MyTransformField.h"

namespace MyTestClassScope
{
	using namespace Niflect;

	class CInheritableTypeReg_CMyTransformFloat
	{
	public:
		static void StaticRegisterType(CNiflectTable& table)
		{
			table.RegisterType<CClass, CMyTransformFloat>("CMyTransformFloat", &StaticCreateFieldLayout, typeid(CMyTransformFloat).hash_code());
		}
		static void StaticInitInheritance()
		{
		}
		static CSharedField StaticCreateFieldLayout()
		{
			auto shared0 = CreateField<CMyTransformFloatField, CMyTransformFloat>();
			auto field0 = shared0.Get();
			return shared0;
		}
	};
}