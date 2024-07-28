#pragma once
#include "Niflect/Base/NiflectMacro.h"
#include "Niflect/Test/TestTypesHeaderForGen0.h"

namespace TestTypesForGen
{
	NIF_T(TaggedTypeData12)
	class CMyClassForGen1_0
	{
		NIF_T(TaggedTypeData13, MyMeta[123, 456, 789])
		class CMyClassForGen1_0_0
		{
		public:
			NIF_F(FieldData28)
			float m_member1_0_0_Float0;
		};
	public:
		NIF_F(FieldData29)
		float m_member1_0_Float0;
	};

	NIF_T(TaggedTypeData14)
	class CMyClassForGen1_1 : public SubScope0::CMyClassForGen0_1
	{
	public:
		NIF_F(FieldData30)
		float m_member1_1_Float0;
	};

	namespace SubScope1
	{
		using namespace TestTypesScope0ForGen::TestTypesScope1ForGen;
		NIF_T(TaggedTypeData15)
		class CMyClassForGen1_2 : public SubScope0::CMyClassForGen0_1
		{
		public:
			NIF_F(FieldData31)
			float m_member1_2_Float_0;
			NIF_F(FieldData32)
			TestTypesScope0ForGen::TestTypesScope1ForGen::CMyClassForGen0_5::EMyEnumOptionStyle0_5_0 m_member1_2_enum_1;
			NIF_F(FieldData33)
			CMyClassForGen0_5::CMyClassForGen0_5_1 m_member1_2_obj_2;
			NIF_F(FieldData34)
			TestTypesScope0ForGen::CMyClassForGen0_3 m_member1_2_obj_3;
			NIF_F(FieldData35)
			CMyClassForGen0_5::EMyEnumOptionStyle0_5_0 m_member1_2_enum_4;
		};
	}
}