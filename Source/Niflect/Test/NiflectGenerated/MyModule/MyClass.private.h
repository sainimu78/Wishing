#pragma once
#include "Niflect/Type/NiflectTable.h"
#include "Niflect/Field/CompoundField.h"
#include "Niflect/Field/ArrayField.h"
#include "Niflect/Field/MapField.h"
#include "Niflect/Test/MyClass.h"
#include "Niflect/Test/MyField.h"
#include "Niflect/Test/MyTransformField.h"
#include "Niflect/Field/PointerField.h"
#include "Niflect/Field/EnumField.h"

namespace MyTestClassScope
{
	using namespace Niflect;

	class CInheritableTypeReg_CMyClass0
	{
	public:
		static void StaticRegisterType(CNiflectTable& table)
		{
			table.RegisterType<CClass, CMyClass0>("CMyClass0", &StaticCreateFieldLayout, typeid(CMyClass0).hash_code());
		}
		static void StaticInitInheritance()
		{
			auto type = CClass::Cast(StaticGetType<CMyClass0>());
			type->InitInheritableTypeMeta(NULL);
		}
		static CSharedField StaticCreateFieldLayout()
		{
			auto shared0 = CreateField<CCompoundField, CMyClass0>();
			auto field0 = shared0.Get();
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_0", GetMemberVariableOffset(&CMyClass0::m_float_0), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_1", GetMemberVariableOffset(&CMyClass0::m_float_1), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType_Misc<CPointerField, float*>("float*");
				auto shared1 = type->CreateFieldLayout();
				auto field1 = Cast<CPointerField>(shared1.Get());
				{
					auto type = StaticGetType<CFloatField>();
					auto shared2 = type->CreateFieldLayout();
					auto field2 = shared2.Get();
					field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
					field1->AddChild(shared2);
				}
				field1->InitMemberMeta("m_float_pointer_2", GetMemberVariableOffset(&CMyClass0::m_float_pointer_2), field0);
				field0->AddChild(shared1);
			}
			return shared0;
		}
	};
	class CInheritableTypeReg_CMyClassBase0
	{
	public:
		static void StaticRegisterType(CNiflectTable& table)
		{
			table.RegisterType<CClass, CMyClassBase0>("CMyClassBase0", &StaticCreateFieldLayout, typeid(CMyClassBase0).hash_code());
		}
		static void StaticInitInheritance()
		{
			auto type = Cast<CClass>(StaticGetType<CMyClassBase0>());
			type->InitInheritableTypeMeta(NULL);
		}
		static CSharedField StaticCreateFieldLayout()
		{
			auto shared0 = CreateField<CCompoundField, CMyClassBase0>();
			auto field0 = shared0.Get();
			{
				auto type = StaticGetType<CStringField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_base_str_0", GetMemberVariableOffset(&CMyClassBase0::m_base_str_0), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_base_float_1", GetMemberVariableOffset(&CMyClassBase0::m_base_float_1), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_base_float_2", GetMemberVariableOffset(&CMyClassBase0::m_base_float_2), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType_Misc<CPointerField, float**>("float**");
				auto shared1 = type->CreateFieldLayout();
				auto field1 = Cast<CPointerField>(shared1.Get());
				{
					auto type = StaticGetType_Misc<CPointerField, float*>("float*");
					auto shared2 = type->CreateFieldLayout();
					auto field2 = Cast<CPointerField>(shared2.Get());
					{
						auto type = StaticGetType<CFloatField>();
						auto shared3 = type->CreateFieldLayout();
						auto field3 = shared3.Get();
						field3->InitMemberMeta("reserved_dim1", CAddrOffset::None, field2);
						field2->AddChild(shared3);
					}
					field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
					field1->AddChild(shared2);
				}
				field1->InitMemberMeta("m_base_float_pointer2D_3", GetMemberVariableOffset(&CMyClassBase0::m_base_float_pointer2D_3), field0);
				field0->AddChild(shared1);
			}
			return shared0;
		}
		static void InvokeMethod_MyFunc0(AddrType obj, AddrType* inputInstanceArray, AddrType* ouputInstanceArray, const TArrayNif<CNiflectType*>& vecInputType, const TArrayNif<CNiflectType*>& vecOutputType)
		{
			auto& arg0 = vecInputType[0]->GetInstanceRef<float>(inputInstanceArray[0]);
			auto& arg1 = vecInputType[1]->GetInstanceRef<CMyClass0>(inputInstanceArray[1]);
			auto& arg2 = vecInputType[2]->GetInstanceRef<bool*>(inputInstanceArray[2]);
			auto& arg3 = vecInputType[3]->GetInstanceRef<CMyClass0*>(inputInstanceArray[3]);
			auto& arg4 = vecInputType[4]->GetInstanceRef<float**>(inputInstanceArray[4]);
			auto& ret0 = vecOutputType[0]->GetInstanceRef<bool>(ouputInstanceArray[0]);
			ret0 = static_cast<CMyClassBase0*>(obj)->MyFunc0(arg0, arg1, arg2, arg3, arg4);
		}
		static void StaticInitMethods()
		{
			auto type = Cast<CClass>(StaticGetType<CMyClassBase0>());
			CNiflectMethod2 method;
			method.m_InvokeFunc = &InvokeMethod_MyFunc0;
			method.m_vecInputType.push_back(StaticGetType<CFloatField>());
			method.m_vecInputType.push_back(StaticGetType<CMyClass0>());
			method.m_vecInputType.push_back(StaticGetType_Misc<CPointerField, bool*>("bool*"));
			method.m_vecInputType.push_back(StaticGetType_Misc<CPointerField, CMyClass0*>("CMyClass0*"));
			method.m_vecInputType.push_back(StaticGetType_Misc<CPointerField, float**>("float**"));
			method.m_vecOutputType.push_back(StaticGetType<CBoolField>());
			type->m_vecMethod.push_back(method);
		}
	};
	class CEnumReg_EMyEnum_OptionStyle
	{
	public:
		static void StaticRegisterType(CNiflectTable& table)
		{
			table.RegisterType<CEnum, EMyEnum_OptionStyle>("EMyEnum_OptionStyle", &StaticCreateFieldLayout, typeid(EMyEnum_OptionStyle).hash_code());
		}
		static void StaticInitEnumMeta()
		{
			auto type = Cast<CEnum>(StaticGetType<EMyEnum_OptionStyle>());
			CEnumMeta meta;
			meta.m_vecEnumConstant.push_back("None");
			meta.m_vecEnumConstant.push_back("Option0");
			meta.m_vecEnumConstant.push_back("Option1");
			meta.m_vecEnumConstant.push_back("Option2");
			type->InitEnumMeta(meta);
		}
		static CSharedField StaticCreateFieldLayout()
		{
			auto shared0 = CreateField<CEnumField, EMyEnum_OptionStyle>();
			auto field0 = shared0.Get();
			return shared0;
		}
	};
	class CInheritableTypeReg_CMyClass1
	{
	public:
		static void StaticRegisterType(CNiflectTable& table)
		{
			table.RegisterType<CClass, CMyClass1>("CMyClass1", &StaticCreateFieldLayout, typeid(CMyClass1).hash_code());
		}
		static void StaticInitInheritance()
		{
			auto type = Cast<CClass>(StaticGetType<CMyClass1>());
			type->InitInheritableTypeMeta(Cast<CClass>(StaticGetType<CMyClassBase0>()));
		}
		static CSharedField StaticCreateFieldLayout()
		{
			auto shared0 = CreateField<CCompoundField, CMyClass1>();
			auto field0 = shared0.Get();
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_0", GetMemberVariableOffset(&CMyClass1::m_float_0), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CMyClass0>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_obj_1", GetMemberVariableOffset(&CMyClass1::m_obj_1), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType_Misc<CArrayField, TArrayNif<float> >("TArrayNif<float>");
				auto shared1 = type->CreateFieldLayout();
				auto field1 = Cast<CArrayField>(shared1.Get());
				{
					auto type = StaticGetType<CFloatField>();
					auto shared2 = type->CreateFieldLayout();
					auto field2 = shared2.Get();
					field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
					field1->AddChild(shared2);
				}
				field1->InitMemberMeta("m_array_2", GetMemberVariableOffset(&CMyClass1::m_array_2), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_3", GetMemberVariableOffset(&CMyClass1::m_float_3), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType_Misc<CArrayField, TArrayNif<CMyClass0> >("TArrayNif<CMyClass0>");
				auto shared1 = type->CreateFieldLayout();
				auto field1 = Cast<CArrayField>(shared1.Get());
				{
					auto type = StaticGetType<CMyClass0>();
					auto shared2 = type->CreateFieldLayout();
					auto field2 = shared2.Get();
					field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
					field1->AddChild(shared2);
				}
				field1->InitMemberMeta("m_array_4", GetMemberVariableOffset(&CMyClass1::m_array_4), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_5", GetMemberVariableOffset(&CMyClass1::m_float_5), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType_Misc<CArrayField, TArrayNif<TArrayNif<float> > >("TArrayNif<TArrayNif<float> >");
				auto shared1 = type->CreateFieldLayout();
				auto field1 = Cast<CArrayField>(shared1.Get());
				{
					auto type = StaticGetType_Misc<CArrayField, TArrayNif<float> >("TArrayNif<float>");
					auto shared2 = type->CreateFieldLayout();
					auto field2 = Cast<CArrayField>(shared2.Get());
					{
						auto type = StaticGetType<CFloatField>();
						auto shared3 = type->CreateFieldLayout();
						auto field3 = shared3.Get();
						field3->InitMemberMeta("reserved_dim1", CAddrOffset::None, field2);
						field2->AddChild(shared3);
					}
					field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
					field1->AddChild(shared2);
				}
				field1->InitMemberMeta("m_array_6", GetMemberVariableOffset(&CMyClass1::m_array_6), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_7", GetMemberVariableOffset(&CMyClass1::m_float_7), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CMyTrasformFloat>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_tm_8", GetMemberVariableOffset(&CMyClass1::m_tm_8), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_9", GetMemberVariableOffset(&CMyClass1::m_float_9), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CStringField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_str_10", GetMemberVariableOffset(&CMyClass1::m_str_10), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_11", GetMemberVariableOffset(&CMyClass1::m_float_11), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType_Misc<CMapField, TMap<Niflect::CString, float> >("TMap<Niflect::CString, float>");
				auto shared1 = type->CreateFieldLayout();
				auto field1 = Cast<CMapField>(shared1.Get());
				{
					auto type = StaticGetType_Misc<CCompoundTemplateField, std::pair<const Niflect::CString, float> >("std::pair<Niflect::CString, float>");
					auto shared2 = type->CreateFieldLayout();
					auto field2 = shared2.Get();
					{
						auto type = StaticGetType<CStringField>();
						auto shared3 = type->CreateFieldLayout();
						auto field3 = shared3.Get();
						field3->InitMemberMeta("key", GetMemberVariableOffset(&std::pair<const Niflect::CString, float>::first), field2);
						field2->AddChild(shared3);
					}
					{
						auto type = StaticGetType<CFloatField>();
						auto shared3 = type->CreateFieldLayout();
						auto field3 = shared3.Get();
						field3->InitMemberMeta("value", GetMemberVariableOffset(&std::pair<const Niflect::CString, float>::second), field2);
						field2->AddChild(shared3);
					}
					field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
					field1->AddChild(shared2);
				}
				field1->InitMemberMeta("m_map_12", GetMemberVariableOffset(&CMyClass1::m_map_12), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_13", GetMemberVariableOffset(&CMyClass1::m_float_13), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<EMyEnum_OptionStyle>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_enum_14", GetMemberVariableOffset(&CMyClass1::m_enum_14), field0);
				field0->AddChild(shared1);
			}
			{
				auto type = StaticGetType<CFloatField>();
				auto shared1 = type->CreateFieldLayout();
				auto field1 = shared1.Get();
				field1->InitMemberMeta("m_float_15", GetMemberVariableOffset(&CMyClass1::m_float_15), field0);
				field0->AddChild(shared1);
			}
			return shared0;
		}
	};
}
