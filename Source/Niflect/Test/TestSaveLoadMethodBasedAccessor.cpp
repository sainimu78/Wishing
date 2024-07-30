#include "Niflect/Serialization/Tree/JsonTreeReadWrite2.h"
#include "Niflect/Memory/Stats/NiflectMemoryStats.h"
#include "Niflect/Test/MyField.h"
#include "Niflect/Test/MyClass.h"
#include "Niflect/Field/CompoundField.h"
#include "Niflect/Field/ArrayField.h"
#include "Niflect/Field/MapField.h"
#include "Niflect/Test/TestModule0.h"
#include "Niflect/Test/MyTransformField.h"
#include "Niflect/Memory/Default/DefaultMemory.h"

#include <iostream>

static void DebugCopyInstance(void* src, void* dst, const Niflect::TArrayNif<Niflect::CField*>& vecField)
{
	using namespace Niflect;
	CString savedData;
	{
		auto& base = src;

		CRwJson::SizeType poolCapa = 0;//Pool的块内存
		CRwJson::SizeType stackCapa = 0;//Json节点或称Object的预留内存
		//CRwJson::AllocatorStack stack;
		//CRwJson::AllocatorPool allocator(poolCapa, &stack);
		CRwJson::AllocatorStack stack;
		auto& allocator = stack;
		CRwJson::Document jd(&allocator, poolCapa, &allocator);
		auto& joRoot = CRwJson::AsRoot(jd);
		CJsonRwDocument doc(jd, joRoot);
		auto rwRoot = doc.GetRootNode();
		for (auto& it : vecField)
			it->SaveToRwNode(base, rwRoot);
		CRwJson::StringBuffer buffer(&allocator, poolCapa);
		CRwJson::WriteToBuffer(joRoot, buffer);
		//printf("%s\n", buffer.GetString());
		savedData = buffer.GetString();
	}
	{
		auto& base = dst;
		using namespace Niflect;
		CRwJson::SizeType poolCapa = 0;//Pool的块内存
		CRwJson::SizeType stackCapa = 0;//Json节点或称Object的预留内存
		//CRwJson::AllocatorStack stack;
		//CRwJson::AllocatorPool allocator(poolCapa, &stack);
		CRwJson::AllocatorStack stack;
		auto& allocator = stack;
		CRwJson::Document jd(&allocator, poolCapa, &allocator);
		auto& joRoot = CRwJson::ReadFromBuffer(jd, savedData.c_str());
		CJsonRwDocument doc(jd, joRoot);
		auto rwRoot = doc.GetRootNode();
		for (auto& it : vecField)
			it->LoadFromRwNode(base, rwRoot);
		CRwJson::StringBuffer buffer(&allocator, poolCapa);
		CRwJson::WriteToBuffer(joRoot, buffer);

		{
			CRwJson::SizeType poolCapa = 0;//Pool的块内存
			CRwJson::SizeType stackCapa = 0;//Json节点或称Object的预留内存
			//CRwJson::AllocatorStack stack;
			//CRwJson::AllocatorPool allocator(poolCapa, &stack);
			CRwJson::AllocatorStack stack;
			auto& allocator = stack;
			CRwJson::Document jd(&allocator, poolCapa, &allocator);
			auto& joRoot = CRwJson::AsRoot(jd);
			CJsonRwDocument doc(jd, joRoot);
			auto rwRoot = doc.GetRootNode();
			for (auto& it : vecField)
				it->SaveToRwNode(base, rwRoot);
			CRwJson::StringBuffer buffer(&allocator, poolCapa);
			CRwJson::WriteToBuffer(joRoot, buffer);
			printf("%s\n", buffer.GetString());
		}
	}
}
static void DebugCopyInstance2(void* src, void* dst, Niflect::CField* field)
{
	Niflect::TArrayNif<Niflect::CField*> vecField;
	vecField.push_back(field);
	DebugCopyInstance(src, dst, vecField);
}
static void TestSingleBuiltInType()
{
	//using namespace MyTestClassScope;
	//using namespace Niflect;
	//
	//auto shared0 = MakeShared<CFloatField>();
	//auto field0 = shared0.Get();
	//
	//float srcData = 123.0f;
	//float dstData;
	//DebugCopyInstance2(&srcData, &dstData, field0);
}
namespace MyTestClassScope
{
	using namespace Niflect;
	void TestInit_CMyClass0_0(CMyClass0_0& srcData)
	{
		const char* fmt = "A number in string %f";
		uint32 cnt = 0;
		auto Inc = [](uint32& cnt)
		{
			return static_cast<float>(++cnt);
		};

		srcData.m_float_0 = Inc(cnt);
		srcData.m_sub_1.m_base_float_0 = Inc(cnt);
		srcData.m_sub_1.m_base_sub_1.m_base_base_float_0 = Inc(cnt);
		srcData.m_sub_1.m_base_sub_1.m_base_base_float_1 = Inc(cnt);
		srcData.m_sub_1.m_base_float_2 = Inc(cnt);
		srcData.m_float_2 = Inc(cnt);
		srcData.m_array_3.push_back(Inc(cnt));
		srcData.m_array_3.push_back(Inc(cnt));
		srcData.m_array_3.push_back(Inc(cnt));
		srcData.m_array_array_4.resize(2);
		srcData.m_array_array_4[0].push_back(Inc(cnt));
		srcData.m_array_array_4[0].push_back(Inc(cnt));
		srcData.m_array_array_4[1].push_back(Inc(cnt));
		srcData.m_array_array_4[1].push_back(Inc(cnt));
		srcData.m_array_array_4[1].push_back(Inc(cnt));
		srcData.m_array_sub_5.resize(2);
		srcData.m_array_sub_5[0].m_base_float_0 = Inc(cnt);
		srcData.m_array_sub_5[0].m_base_sub_1.m_base_base_float_0 = Inc(cnt);
		srcData.m_array_sub_5[0].m_base_sub_1.m_base_base_float_1 = Inc(cnt);
		srcData.m_array_sub_5[0].m_base_float_2 = Inc(cnt);
		srcData.m_array_sub_5[1].m_base_float_0 = Inc(cnt);
		srcData.m_array_sub_5[1].m_base_sub_1.m_base_base_float_0 = Inc(cnt);
		srcData.m_array_sub_5[1].m_base_sub_1.m_base_base_float_1 = Inc(cnt);
		srcData.m_array_sub_5[1].m_base_float_2 = Inc(cnt);
		srcData.m_tm_6.m_translation.m_x = Inc(cnt);
		srcData.m_tm_6.m_translation.m_y = Inc(cnt);
		srcData.m_tm_6.m_translation.m_z = Inc(cnt);
		srcData.m_tm_6.m_rotation.m_x = Inc(cnt);
		srcData.m_tm_6.m_rotation.m_y = Inc(cnt);
		srcData.m_tm_6.m_rotation.m_z = Inc(cnt);
		srcData.m_tm_6.m_rotation.m_w = Inc(cnt);
		srcData.m_tm_6.m_scale.m_x = Inc(cnt);
		srcData.m_tm_6.m_scale.m_y = Inc(cnt);
		srcData.m_tm_6.m_scale.m_z = Inc(cnt);
		srcData.m_map_7[Inc(cnt)] = Inc(cnt);
		srcData.m_map_7[Inc(cnt)] = Inc(cnt);
		srcData.m_map_7[Inc(cnt)] = Inc(cnt);
		srcData.m_map_8["Bucuo"] = Inc(cnt);
		srcData.m_map_8["Shima"] = Inc(cnt);
	}
}
	
static void TestSimpleClass()
{
	//using namespace MyTestClassScope;
	//using namespace Niflect;
	//
	//auto shared0 = MakeShared<CCompoundField>();
	//auto field0 = shared0.Get();
	//CreateMyClassBase0_0_0(field0);

	//CMyClassBase0_0_0 srcData;
	//srcData.m_base_base_float_0 = 1.23f;
	//srcData.m_base_base_float_1 = 4.56f;
	//CMyClassBase0_0_0 dstData;
	//DebugCopyInstance2(&srcData, &dstData, field0);
}

namespace MyTestClassScope
{
	enum class ETestAccessorType
	{
		AddrOnly,
		BothAddrAndMethod,
		BothAddrAndMethodCopyGetter,
	};
	static const ETestAccessorType g_accessorType = ETestAccessorType::BothAddrAndMethodCopyGetter;

	CSharedField CreateFieldLayout_CMyClassBase0_0_0()
	{
		auto shared0 = MakeShared<CCompoundField>();
		auto field0 = shared0.Get();
		{
			auto shared1 = MakeShared<CFloatField>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClassBase0_0_0::m_base_base_float_0));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_base_base_float_0", field0);
			field0->AddChild(shared1);
		}
		switch (g_accessorType)
		{
		case ETestAccessorType::AddrOnly:
		{
			auto shared1 = MakeShared<CFloatField>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClassBase0_0_0::m_base_base_float_1));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_base_base_float_1", field0);
			field0->AddChild(shared1);
		}
		break;
		case ETestAccessorType::BothAddrAndMethod:
		case ETestAccessorType::BothAddrAndMethodCopyGetter:
		{
			auto shared1 = MakeShared<CFloatField>();
			auto field1 = shared1.Get();
			field1->InitAccessorGetter(MakeShared<TAccessorMethodGetter<TAccessorMethodHasConst<CMyClassBase0_0_0, float> > >(&CMyClassBase0_0_0::GetBaseBaseFloat1));
			field1->InitAccessorSetter(MakeShared<TAccessorMethodSetter<TAccessorMethodNonConst<CMyClassBase0_0_0, void, float>, float> >(&CMyClassBase0_0_0::SetBaseBaseFloat1));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_base_base_float_1", field0);
			field0->AddChild(shared1);
		}
		break;
		default:
			ASSERT(false);
			break;
		}
		return shared0;
	}
	CSharedField CreateFieldLayout_CMyClassBase0_0()
	{
		auto shared0 = MakeShared<CCompoundField>();
		auto field0 = shared0.Get();
		{
			auto shared1 = MakeShared<CFloatField>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClassBase0_0::m_base_float_0));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_base_float_0", field0);
			field0->AddChild(shared1);
		}
		switch (g_accessorType)
		{
		case ETestAccessorType::AddrOnly:
		{
			auto shared1 = CreateFieldLayout_CMyClassBase0_0_0();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClassBase0_0::m_base_sub_1));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_base_sub_1", field0);
			field0->AddChild(shared1);
		}
		break;
		case ETestAccessorType::BothAddrAndMethod:
		{
			auto shared1 = CreateFieldLayout_CMyClassBase0_0_0();
			auto field1 = shared1.Get();
			field1->InitAccessorGetter(MakeShared<TAccessorMethodGetter<TAccessorMethodHasConst<CMyClassBase0_0, const CMyClassBase0_0_0&> > >(&CMyClassBase0_0::GetBaseSub1));
			field1->InitAccessorSetter(MakeShared<TAccessorMethodSetter<TAccessorMethodNonConst<CMyClassBase0_0, void, const CMyClassBase0_0_0&>, CMyClassBase0_0_0> >(&CMyClassBase0_0::SetBaseSub1));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_base_sub_1", field0);
			field0->AddChild(shared1);
		}
		break;
		case ETestAccessorType::BothAddrAndMethodCopyGetter:
		{
			auto shared1 = CreateFieldLayout_CMyClassBase0_0_0();
			auto field1 = shared1.Get();
			field1->InitAccessorGetter(MakeShared<TAccessorMethodGetter<TAccessorMethodHasConst<CMyClassBase0_0, CMyClassBase0_0_0> > >(&CMyClassBase0_0::GetBaseSub1_Copy));
			field1->InitAccessorSetter(MakeShared<TAccessorMethodSetter<TAccessorMethodNonConst<CMyClassBase0_0, void, const CMyClassBase0_0_0&>, CMyClassBase0_0_0> >(&CMyClassBase0_0::SetBaseSub1));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_base_sub_1", field0);
			field0->AddChild(shared1);
		}
		break;
		default:
			ASSERT(false);
			break;
		}
		{
			auto shared1 = MakeShared<CFloatField>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClassBase0_0::m_base_float_2));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_base_float_2", field0);
			field0->AddChild(shared1);
		}
		return shared0;
	}
	CSharedField CreateFieldLayout_CMyClass0_0()
	{
		auto shared0 = MakeShared<CCompoundField>();
		auto field0 = shared0.Get();
		{
			auto shared1 = MakeShared<CFloatField>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClass0_0::m_float_0));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_float_0", field0);
			field0->AddChild(shared1);
		}
		switch (g_accessorType)
		{
		case ETestAccessorType::AddrOnly:
		{
			auto shared1 = CreateFieldLayout_CMyClassBase0_0();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClass0_0::m_sub_1));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_sub_1", field0);
			field0->AddChild(shared1);
		}
		break;
		case ETestAccessorType::BothAddrAndMethod:
		{
			auto shared1 = CreateFieldLayout_CMyClassBase0_0();
			auto field1 = shared1.Get();
			field1->InitAccessorGetter(MakeShared<TAccessorMethodGetter<TAccessorMethodHasConst<CMyClass0_0, const CMyClassBase0_0&> > >(&CMyClass0_0::GetSub1));
			field1->InitAccessorSetter(MakeShared<TAccessorMethodSetter<TAccessorMethodNonConst<CMyClass0_0, void, const CMyClassBase0_0&>, CMyClassBase0_0> >(&CMyClass0_0::SetSub1));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_sub_1", field0);
			field0->AddChild(shared1);
		}
		break;
		case ETestAccessorType::BothAddrAndMethodCopyGetter:
		{
			auto shared1 = CreateFieldLayout_CMyClassBase0_0();
			auto field1 = shared1.Get();
			field1->InitAccessorGetter(MakeShared<TAccessorMethodGetter<TAccessorMethodHasConst<CMyClass0_0, CMyClassBase0_0> > >(&CMyClass0_0::GetSub1_Copy));
			field1->InitAccessorSetter(MakeShared<TAccessorMethodSetter<TAccessorMethodNonConst<CMyClass0_0, void, const CMyClassBase0_0&>, CMyClassBase0_0> >(&CMyClass0_0::SetSub1));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_sub_1", field0);
			field0->AddChild(shared1);
		}
		break;
		default:
			ASSERT(false);
			break;
		}
		{
			auto shared1 = MakeShared<CFloatField>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClass0_0::m_float_2));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_float_2", field0);
			field0->AddChild(shared1);
		}
		switch (g_accessorType)
		{
		case ETestAccessorType::AddrOnly:
		{
			auto shared1 = CreateField<CArrayField, TArrayNif<float> >();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClass0_0::m_array_3));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_array_3", field0);
			{
				auto shared2 = MakeShared<CFloatField>();
				auto field2 = shared2.Get();
				field1->InitAccessors();
				field2->InitMemberMeta_ReservedForMethodBasedAccessor("reserved_dim0", field1);
				field1->AddChild(shared2);
			}
			field0->AddChild(shared1);
		}
		break;
		case ETestAccessorType::BothAddrAndMethod:
		{
			auto shared1 = MakeShared<CArrayField>();
			auto field1 = shared1.Get();
			field1->InitAccessorGetter(MakeShared<TAccessorMethodGetter<TAccessorMethodHasConst<CMyClass0_0, const TArrayNif<float>& > > >(&CMyClass0_0::GetArray));
			field1->InitAccessorSetter(MakeShared<TAccessorMethodSetter<TAccessorMethodNonConst<CMyClass0_0, void, const TArrayNif<float>&>, TArrayNif<float> > >(&CMyClass0_0::SetArray));
			field1->InitDelegate(MakeShared<TArrayDelegateStlCompliant<TArrayNif<float> > >());
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_array_3", field0);
			{
				auto shared2 = MakeShared<CFloatField>();
				auto field2 = shared2.Get();
				field2->InitAccessors();
				field2->InitMemberMeta_ReservedForMethodBasedAccessor("reserved_dim0", field1);
				field1->AddChild(shared2);
			}
			field0->AddChild(shared1);
		}
		break;
		case ETestAccessorType::BothAddrAndMethodCopyGetter:
		{
			if (false)
			{
				auto shared1 = MakeShared<Reserved_AccessorDelegatesBased_CArrayField>();
				auto field1 = shared1.Get();
				field1->InitAccessors();
				field1->SetGetElementsCount(MakeShared<TArrayAccessorMemberFunctionGetElementsCount<TAccessorMethodHasConst<CMyClass0_0, uint32> > >(&CMyClass0_0::GetArrayCount));
				field1->SetSetElementsCount(MakeShared<TArrayAccessorMemberFunctionSetElementsCount<TAccessorMethodNonConst<CMyClass0_0, void, uint32> > >(&CMyClass0_0::SetArrayCount));
				field1->SetSaveElementToRwNode(MakeShared<TArrayAccessorMemberFunctionSaveElementToRwNode<TAccessorMethodHasConst<CMyClass0_0, float, uint32> > >(&CMyClass0_0::GetArrayFloat));
				field1->SetLoadElementFromRwNode(MakeShared<TArrayAccessorMemberFunctionLoadElementFromRwNode<float, TAccessorMethodNonConst<CMyClass0_0, void, const float&, uint32> > >(&CMyClass0_0::SetArrayFloat));
				field1->SetCreateElementPropertyTree(MakeShared<TArrayAccessorMemberFunctionCreateElementPropertyTree<TAccessorMethodHasConst<CMyClass0_0, float, uint32> > >(&CMyClass0_0::GetArrayFloat));
				field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_array_3", field0);
				{
					auto shared2 = MakeShared<CFloatField>();
					auto field2 = shared2.Get();
					field2->InitAccessors();
					field2->InitMemberMeta_ReservedForMethodBasedAccessor("reserved_dim0", field1);
					field1->AddChild(shared2);
				}
				field0->AddChild(shared1);
			}
			if (true)
			{
				auto shared1 = MakeShared<CArrayField>();
				auto field1 = shared1.Get();
				field1->InitAccessorGetter(MakeShared<TAccessorMethodGetter<TAccessorMethodHasConst<CMyClass0_0, TArrayNif<float> > > >(&CMyClass0_0::GetArray_Copy));
				field1->InitAccessorSetter(MakeShared<TAccessorMethodSetter<TAccessorMethodNonConst<CMyClass0_0, void, const TArrayNif<float>&>, TArrayNif<float> > >(&CMyClass0_0::SetArray));
				field1->InitDelegate(MakeShared<TArrayDelegateStlCompliant<TArrayNif<float> > >());
				field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_array_3", field0);
				{
					auto shared2 = MakeShared<CFloatField>();
					auto field2 = shared2.Get();
					field2->InitAccessors();
					field2->InitMemberMeta_ReservedForMethodBasedAccessor("reserved_dim0", field1);
					field1->AddChild(shared2);
				}
				field0->AddChild(shared1);
			}
		}
		break;
		default:
			ASSERT(false);
			break;
		}
		{
			auto shared1 = CreateField<CArrayField, TArrayNif<TArrayNif<float> >>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClass0_0::m_array_array_4));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_array_array_4", field0);
			{
				auto shared2 = CreateField<CArrayField, TArrayNif<float>>();
				auto field2 = shared2.Get();
				field2->InitAccessors();
				field2->InitMemberMeta_ReservedForMethodBasedAccessor("reserved_dim0", field1);
				{
					auto shared3 = MakeShared<CFloatField>();
					auto field3 = shared3.Get();
					field3->InitAccessors();
					field3->InitMemberMeta_ReservedForMethodBasedAccessor("reserved_dim1", field2);
					field2->AddChild(shared3);
				}
				field1->AddChild(shared2);
			}
			field0->AddChild(shared1);
		}
		{
			auto shared1 = CreateField<CArrayField, TArrayNif<CMyClassBase0_0> >();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClass0_0::m_array_sub_5));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_array_sub_5", field0);
			{
				auto shared2 = CreateFieldLayout_CMyClassBase0_0();
				auto field2 = shared2.Get();
				field2->InitAccessors();
				field2->InitMemberMeta_ReservedForMethodBasedAccessor("reserved_dim0", field1);
				field1->AddChild(shared2);
			}
			field0->AddChild(shared1);
		}
		{
			auto shared1 = MakeShared<CMyTransformFloatField>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClass0_0::m_tm_6));
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_tm_6", field0);
			field0->AddChild(shared1);
		}
		{
			auto shared1 = MakeShared<CMapField>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClass0_0::m_map_7));
			field1->InitDelegate(MakeShared<TMapDelegateStlCompliant<TMap<float, float> > >());
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_map_7", field0);
			{
				auto shared2 = MakeShared<CPairField>();
				auto field2 = shared2.Get();
				field2->InitAccessors();
				field2->InitMemberMeta_ReservedForMethodBasedAccessor("reserved_dim0", field1);
				{
					auto shared3 = MakeShared<CFloatField>();
					auto field3 = shared3.Get();
					field3->InitAccessorsAddrBased(GetMemberVariableOffset(&std::pair<const float, float>::first));
					field3->InitMemberMeta_ReservedForMethodBasedAccessor("key", field2);
					field2->AddChild(shared3);
				}
				{
					auto shared3 = MakeShared<CFloatField>();
					auto field3 = shared3.Get();
					field3->InitAccessorsAddrBased(GetMemberVariableOffset(&std::pair<const float, float>::second));
					field3->InitMemberMeta_ReservedForMethodBasedAccessor("value", field2);
					field2->AddChild(shared3);
				}
				field1->AddChild(shared2);
			}
			field0->AddChild(shared1);
		}
		{
			auto shared1 = MakeShared<CMapField>();
			auto field1 = shared1.Get();
			field1->InitAccessorsAddrBased(GetMemberVariableOffset(&CMyClass0_0::m_map_8));
			field1->InitDelegate(MakeShared<TMapDelegateStlCompliant<TMap<CString, float> > >());
			field1->InitMemberMeta_ReservedForMethodBasedAccessor("m_map_8", field0);
			{
				auto shared2 = MakeShared<CPairField>();
				auto field2 = shared2.Get();
				field2->InitAccessors();
				field2->InitMemberMeta_ReservedForMethodBasedAccessor("reserved_dim0", field1);
				{
					auto shared3 = MakeShared<CStringField>();
					auto field3 = shared3.Get();
					field3->InitAccessorsAddrBased(GetMemberVariableOffset(&std::pair<const CString, float>::first));
					field3->InitMemberMeta_ReservedForMethodBasedAccessor("key", field2);
					field2->AddChild(shared3);
				}
				{
					auto shared3 = MakeShared<CFloatField>();
					auto field3 = shared3.Get();
					field3->InitAccessorsAddrBased(GetMemberVariableOffset(&std::pair<const CString, float>::second));
					field3->InitMemberMeta_ReservedForMethodBasedAccessor("value", field2);
					field2->AddChild(shared3);
				}
				field1->AddChild(shared2);
			}
			field0->AddChild(shared1);
		}
		return shared0;
	}
}

static void TestSimpleClass2()
{
	using namespace MyTestClassScope;
	using namespace Niflect;
	
	auto shared0 = CreateFieldLayout_CMyClass0_0();
	auto field0 = shared0.Get();
	field0->InitAccessors();

	CMyClass0_0 srcData2;
	TestInit_CMyClass0_0(srcData2);
	CMyClass0_0& srcData = srcData2;
	CMyClass0_0 dstData;
	DebugCopyInstance2(&srcData, &dstData, field0);
}
static void TestDefaultArray()
{
	//using namespace MyTestClassScope;
	//using namespace Niflect;
	//
	//auto shared0 = CreateField<CArrayField, TArrayNif<float> >();
	//auto field0 = shared0.Get();
	//{
	//	auto shared1 = CreateField<CFloatField, CFloatField>();
	//	auto field1 = shared1.Get();
	//	field1->InitMemberMeta("reserved_dim0", CAddrOffset::None, field0);
	//	field0->AddChild(shared1);
	//}

	//TArrayNif<float> srcData;
	//srcData.push_back(1.0f);
	//srcData.push_back(2.0f);
	//TArrayNif<float> dstData;
	//DebugCopyInstance2(&srcData, &dstData, field0);
}
static void TestTypicalClass()
{
	using namespace MyTestClassScope;
	using namespace Niflect;
	
	TArrayNif<CField*> vecField;
	auto baseType = StaticGetType<CMyClassBase0>();
	auto derivedType = StaticGetType<CMyClass1>();
	auto baseField = baseType->GetRootField();
	auto derivedField = derivedType->GetRootField();
	vecField.push_back(baseField);
	vecField.push_back(derivedField);

	CMyClass1 srcData;
	TestInit_CMyClass1(srcData);
	CMyClass1 dstData;
	DebugCopyInstance(&srcData, &dstData, vecField);
}
static void TestCustomField()
{
	//using namespace MyTestClassScope;
	//using namespace Niflect;
	//
	//auto shared0 = CreateField<TMyTransformField<float>, TMyTransform<float> >();
	//auto field0 = shared0.Get();

	//TMyTransform<float> srcData;
	//TestInit_TMyTransform(srcData);
	//TMyTransform<float> dstData;
	//DebugCopyInstance2(&srcData, &dstData, field0);
}
static void TestPair()
{
	//using namespace MyTestClassScope;
	//using namespace Niflect;
	////
	//auto shared0 = MakeShared<CCompoundField>();
	//auto field0 = shared0.Get();
	//{
	//	auto shared1 = Niflect::MakeShared<CStringField>();
	//	auto field1 = shared1.Get();
	//	field1->InitMemberMeta("first", GetMemberVariableOffset(&std::pair<CString, float>::first), field0);
	//	field0->AddChild(shared1);
	//}
	//{
	//	auto shared1 = Niflect::MakeShared<CFloatField>();
	//	auto field1 = shared1.Get();
	//	field1->InitMemberMeta("second", GetMemberVariableOffset(&std::pair<CString, float>::second), field0);
	//	field0->AddChild(shared1);
	//}

	//std::pair<CString, float> srcData;
	//srcData.first = "Nihao";
	//srcData.second = 1.0f;
	//std::pair<CString, float> dstData;
	//DebugCopyInstance2(&srcData, &dstData, field0);
}

static void MyExp()
{
	auto memTest = Niflect::DebugGetMemoryStats();
	TestCreateModuleReg0();
	//TestSingleBuiltInType();
	//TestSimpleClass();
	TestSimpleClass2();
	//TestDefaultArray();
	//TestTypicalClass();
	//TestCustomField();
	//TestDefaultMap();
	//TestPair();
	TestDestroyModuleReg0();
	printf("");
}

#ifdef TEST_FOR_GCC
#else
#include <Windows.h>
class CStaticTest
{
public:
	CStaticTest()
	{
#ifdef WIN32
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
#endif
		MyExp();
	}
};
//CStaticTest s;
#endif

#ifdef TEST_FOR_GCC
int main()
{
	MyExp();
	return 0;
}
#else
#endif