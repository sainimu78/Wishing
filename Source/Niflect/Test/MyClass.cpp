//#include "Niflect/Test2/MyClass2.h"
//#include "Niflect/Test2/MyField2.h"
//#include "Niflect/Field/ArrayField.h"
//#include "Niflect/Field/CompoundField.h"
//#include "Niflect/Field/MapField.h"
//
//namespace MyTestClassScope
//{
//	using namespace Niflect;
//
//	CSharedField CreateFieldTree_CMyClass0()
//	{
//		auto shared0 = MakeShared<CCompoundField>();
//		auto field0 = shared0.Get();
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_float_0", GetMemberVariableOffset(&CMyClass0::m_float_0), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_float_1", GetMemberVariableOffset(&CMyClass0::m_float_1), field0);
//			field0->AddChild(shared1);
//		}
//		return shared0;
//	}
//	CSharedField CreateFieldTree_CMyClassBase0()
//	{
//		auto shared0 = MakeShared<CCompoundField>();
//		auto field0 = shared0.Get();
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_base_float_0", GetMemberVariableOffset(&CMyClassBase0::m_base_float_0), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_base_float_1", GetMemberVariableOffset(&CMyClassBase0::m_base_float_1), field0);
//			field0->AddChild(shared1);
//		}
//		return shared0;
//	}
//	CSharedField CreateFieldTree_CMyClass1()
//	{
//		auto shared0 = MakeShared<CCompoundField>();
//		auto field0 = shared0.Get();
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_float_0", GetMemberVariableOffset(&CMyClass1::m_float_0), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = CreateFieldTree_CMyClass0();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_obj_1", GetMemberVariableOffset(&CMyClass1::m_obj_1), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = CreateArrayField<TArrayNif<float> >();
//			auto field1 = shared1.Get();
//			{
//				auto shared2 = Niflect::MakeShared<CFloatField>();
//				auto field2 = shared2.Get();
//				field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
//				field1->SetElementField(shared2);
//			}
//			field1->InitMemberMeta("m_array_2", GetMemberVariableOffset(&CMyClass1::m_array_2), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_float_3", GetMemberVariableOffset(&CMyClass1::m_float_3), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = CreateArrayField<TArrayNif<CMyClass0> >();
//			auto field1 = shared1.Get();
//			{
//				auto shared2 = CreateFieldTree_CMyClass0();
//				auto field2 = shared2.Get();
//				field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
//				field1->SetElementField(shared2);
//			}
//			field1->InitMemberMeta("m_array_4", GetMemberVariableOffset(&CMyClass1::m_array_4), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_float_5", GetMemberVariableOffset(&CMyClass1::m_float_5), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = CreateArrayField<TArrayNif<TArrayNif<float> > >();
//			auto field1 = shared1.Get();
//			{
//				auto shared2 = CreateArrayField<TArrayNif<float> >();
//				auto field2 = shared2.Get();
//				{
//					auto shared3 = Niflect::MakeShared<CFloatField>();
//					auto field3 = shared3.Get();
//					field3->InitMemberMeta("reserved_dim1", CAddrOffset::None, field2);
//					field2->SetElementField(shared3);
//				}
//				field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
//				field1->SetElementField(shared2);
//			}
//			field1->InitMemberMeta("m_array_6", GetMemberVariableOffset(&CMyClass1::m_array_6), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_float_7", GetMemberVariableOffset(&CMyClass1::m_float_7), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<TMyTransformField<float> >();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_tm_8", GetMemberVariableOffset(&CMyClass1::m_tm_8), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_float_9", GetMemberVariableOffset(&CMyClass1::m_float_9), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<CStringField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_str_10", GetMemberVariableOffset(&CMyClass1::m_str_10), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_float_11", GetMemberVariableOffset(&CMyClass1::m_float_11), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = CreateMapField<TMap<Niflect::CString, float> >();
//			auto field1 = shared1.Get();
//			{
//				auto shared2 = Niflect::MakeShared<CCompoundField>();
//				auto field2 = shared2.Get();
//				{
//					auto shared3 = Niflect::MakeShared<CStringField>();
//					auto field3 = shared3.Get();
//					field3->InitMemberMeta("key", GetMemberVariableOffset(&TMap<Niflect::CString, float>::allocator_type::value_type::first), field2);
//					field2->AddChild(shared3);
//				}
//				{
//					auto shared3 = Niflect::MakeShared<CFloatField>();
//					auto field3 = shared3.Get();
//					field3->InitMemberMeta("value", GetMemberVariableOffset(&TMap<Niflect::CString, float>::allocator_type::value_type::second), field2);
//					field2->AddChild(shared3);
//				}
//				field2->InitMemberMeta("reserved_dim0", CAddrOffset::None, field1);
//				field1->SetElementField(shared2);
//			}
//			field1->InitMemberMeta("m_map_12", GetMemberVariableOffset(&CMyClass1::m_map_12), field0);
//			field0->AddChild(shared1);
//		}
//		{
//			auto shared1 = Niflect::MakeShared<CFloatField>();
//			auto field1 = shared1.Get();
//			field1->InitMemberMeta("m_float_13", GetMemberVariableOffset(&CMyClass1::m_float_13), field0);
//			field0->AddChild(shared1);
//		}
//		return shared0;
//	}
//}