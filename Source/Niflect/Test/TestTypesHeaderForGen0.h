#pragma once
#include "Niflect/Base/NiflectMacro.h"
#include <cstddef>
#include "Niflect/Test/TestDebugArray.h"

namespace TestTypesScope0ForGen
{
	namespace TestTypesScope1ForGen
	{
		class CMyClassForGen2_1;
	}
}
namespace TestTypesScope0ForGen
{
	class CMyClassForGen0_4;
}
		
namespace TestTypesForGen
{
	class CMySubClass
	{
	public:
		CMySubClass()
			: m_memberFloatOfSub0(0.0f)
		{

		}
		float m_memberFloatOfSub0;
	};

	NIF_T(TaggedTypeData0_0)
	class CMySubClass1
	{
	public:
		float m_memberFloatOfSub0;
	};
	
	NIF_T(TaggedTypeData0)
	enum EMyEnumMaskStyle
	{
		MEMS_None NIF_C(Nihao0), 
		MEMS_First NIF_C(Nihao1),
		MEMS_Second ,
		MEMS_Count NIF_C(Nihao3),
	};

	typedef float MyFFFFFFFFFloat;
	
	using MyAliasFloat = float;
	
	typedef MyFFFFFFFFFloat MyFloatTypedef2;
	
	typedef MyAliasFloat MyFloatTypedef3;
	
	using MyFloatAlias4 = MyFloatTypedef3;

	typedef CMySubClass1 MyClassTypedef0;
	
	using MyClassAlias0 = CMySubClass1;
	
	typedef MyClassTypedef0 MyClassTypedef1;
	
	using MyClassAlias1 = MyClassAlias0;
	
	typedef MyClassAlias1 MyClassTypedef2;
	
	using MyClassAlias2 = MyClassTypedef2;
	
	//using namespace TestContainer;

	NIF_T(TaggedTypeData1)
	struct SMyStruct0
	{
		NIF_F(FieldData0_0_0)
		TestContainer::TMyArrayDebug<TestContainer::TMyArrayDebug<float> > m_member0_array_0_0_0;
		NIF_F(FieldData0_0)
		TestContainer::TMyArrayDebug<float> m_member0_array_0_0;
		NIF_F(FieldData0_0)
		CMySubClass1 m_member0_sub_0_0;
		NIF_F(FieldData0_1)
		MyClassTypedef0 m_member0_sub_0_1;
		NIF_F(FieldData0_2)
		MyClassAlias0 m_member0_sub_0_2;
		NIF_F(FieldData0_3)
		MyClassTypedef1 m_member0_sub_0_3;
		NIF_F(FieldData0_4)
		MyClassAlias1 m_member0_sub_0_4;
		NIF_F(FieldData0_5)
		MyClassTypedef2 m_member0_sub_0_5;
		NIF_F(FieldData0_6)
		MyClassAlias2 m_member0_sub_0_6;
		NIF_F(FieldData0)
		float m_member0_float_0;
		NIF_F(FieldData1)
		bool m_member0_bool_1;
		NIF_F(FieldData1_0)
		MyFFFFFFFFFloat m_member0_MyFloat_2;
		NIF_F(FieldData1_1)
		MyAliasFloat m_member0_AliasFloat_3;
		NIF_F(FieldData1_2)
		MyFloatTypedef2 m_member0_TypedefFloat_4;
		NIF_F(FieldData1_3)
		MyFloatTypedef3 m_member0_TypedefFloat_5;
		NIF_F(FieldData1_4)
		MyFloatAlias4 m_member0_AliasFloat_6;
	};

	class CMyBaseNotForGen
	{
	public:
		float m_memberNotForGen;
	};
	
#define SOME_OTHER_MACRO_FOR_NIF_T_TEST typedef void* ATypeDefinedBySomeOtherMacro;

	class CMyClassForGen2_0;
	enum class EMyEnumOptionStyle;

	NIF_T(TaggedTypeData2)
	class CMyBase0 : private CMyBaseNotForGen
	{
	public:
		CMyBase0();

	public:
		NIF_F(FieldData2)
		float m_memberBase0Float_0;
		bool m_memberBase0Bool_1;
		//NIF_F(FieldData3)
		//TestTypesScope0ForGen::CMyClassForGen0_4* m_memberBase_pointer_2;
		//NIF_F(FieldData3_0)
		//CMyClassForGen2_0* m_memberBasePointer_3;
		//NIF_F(FieldData3_1)
		//CMyBase0* m_memberBase_pointer_4;
		NIF_F(FieldData3_2)
		EMyEnumOptionStyle m_memberBase_enum_5;

	private:
		float GetFromPointer() const;
	};
	
	NIF_T(TaggedTypeData3)
	enum class EMyEnumOptionStyle
	{
		None,
		First,
		Second,
		Third,
	};

	NIF_T(TaggedTypeData4, Meta=(Shima, Bucuo))
	class CMyClassForGen0_0
	{
	public:
		CMyClassForGen0_0()
			: m_member0_0_Float_0(123.0f)
		{
		}
		NIF_F(FieldData4)
		float m_member0_0_Float_0;
		NIF_F(FieldData5)
		TestContainer::TMyArrayDebug<float> m_member0_0_ArrayFloat_1;
		NIF_M()
		float Member0_0_MyFunc()
		{
			float a = 1.0f;
			float b = 2.0f;
			return a+b;
		}
		//NIF_F(FieldData6)
		//CMySubClass m_member0_0_sub_2;
		NIF_F(FieldData6_0)
		TestContainer::TMyArrayDebug<TestContainer::TMyArrayDebug<float> > m_member0_0_ArrayFloat_2_0;
		NIF_F(FieldData6_1)
		TestContainer::TMyArrayDebug<CMySubClass> m_member0_0_ArraySubClass_2_1;//itemÎ´×¢²áÓ¦±¨´í
		NIF_F(FieldData6_2)
		TestContainer::TMyArrayDebug<CMyBase0> m_member0_0_ArrayBase_2_2;
		NIF_F(FieldData6_3)
		TestContainer::TMyArrayDebug<TestContainer::TMyArrayDebug<CMyBase0> > m_member0_0_ArrayArrayBase_2_3;
		NIF_F(FieldData7)
		EMyEnumMaskStyle m_member0_0_enumMask_3;
		NIF_F(FieldData8)
		EMyEnumOptionStyle m_member0_0_enumOption_4;
	};
	
	namespace SubScope0
	{
		NIF_T(TaggedTypeData5)
		class CMyClassForGen0_1 : public CMyBase0
		{
		public:
			NIF_F(FieldData9)
			float m_member0_1_Float_0;
			NIF_F(FieldData10)
			TestContainer::TMyArrayDebug<float> m_member0_1_ArrayFloat_1;
			NIF_F(FieldData11)
			CMySubClass m_member0_1_sub_2;
		};

		using namespace TestTypesScope0ForGen::TestTypesScope1ForGen;
		
		NIF_T(TaggedTypeData6)
		class CMyClassForGen0_2 : public CMyBase0
		{
		public:
			CMyClassForGen0_2()
				: m_member0_2_pointer_2(NULL)
			{
			}
			NIF_F(FieldData12)
			float m_member0_2_Float_0;
			NIF_F(FieldData13)
			TestContainer::TMyArrayDebug<float> m_member0_2_ArrayFloat_1;
			NIF_F(FieldData14)
			CMyClassForGen2_1* m_member0_2_pointer_2;
		};
	}
}

namespace TestTypesScope0ForGen
{
	NIF_T(TaggedTypeData7)
	class CMyClassForGen0_3
	{
	public:
		NIF_F(FieldData15)
		TestTypesForGen::EMyEnumOptionStyle m_member0_3_Float_0;
		NIF_F(FieldData16)
		bool m_member0_3_Bool_1;
		NIF_F(FieldData17)
		TestTypesForGen::SubScope0::CMyClassForGen0_1 m_member0_3_Float_2;
	};

	NIF_T(TaggedTypeData8)
	class CMyClassForGen0_4 : public TestTypesForGen::SubScope0::CMyClassForGen0_1
	{
	public:
		NIF_F(FieldData18)
		bool m_member0_4_Bool_0;
		NIF_F(FieldData19)
		float m_member0_4_Float_1;
	};
	
	namespace TestTypesScope1ForGen
	{
		using namespace TestTypesForGen;

		NIF_T(TaggedTypeData9)
		class CMyClassForGen0_5 : public CMyBase0
		{
		public:
			NIF_T(TaggedTypeData10)
			enum class EMyEnumOptionStyle0_5_0
			{
				None,
				First,
				Second,
				Third,
				Forth,
			};
			NIF_T(TaggedTypeData11)
			class CMyClassForGen0_5_1 : public SubScope0::CMyClassForGen0_1
			{
			public:
				NIF_F(FieldData20)
				float m_member0_5_1_Float_0;
				NIF_F(FieldData21)
				TestContainer::TMyArrayDebug<float> m_member0_5_1_ArrayFloat_1;
				NIF_F(FieldData22)
				CMySubClass m_member0_5_1_sub_2;
			};

		public:
			CMyClassForGen0_5();
			NIF_F(FieldData23)
			float m_member0_5_Float_0;
			NIF_F(FieldData24)
			TestContainer::TMyArrayDebug<float> m_member0_5_ArrayFloat_1;
			NIF_M()
			float Member0_5_MyFunc(float arg0, bool arg1, CMyClassForGen0_0& arg2, const CMyClassForGen0_0& arg3, CMyBase0* arg4, TestContainer::TMyArrayDebug<float>& arg5, TestContainer::TMyArrayDebug<bool> arg6, void* arg7 = NULL, float arg8 = 123.0f)
			{
				float a = 1.0f;
				float b = 2.0f;
				return a+b;
			}
			NIF_F(FieldData25)
			CMySubClass m_member0_5_sub_2;
			NIF_F(FieldData26)
			EMyEnumMaskStyle m_member0_5_enumMask_3;
			NIF_F(FieldData27)
			EMyEnumOptionStyle m_member0_5_enumOption_4;
		};
	}
}

//#include <vector>
//NIF_T(TaggedTypeData222222)
//class FFFFFFFF
//{
//public:
//	NIF_F(FieldData33333333)
//	std::vector<float> m_vec;
//};