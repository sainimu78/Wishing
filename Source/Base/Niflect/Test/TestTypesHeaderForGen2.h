#pragma once
#include "Niflect/Base/NiflectMacro.h"

namespace TestTypesForGen
{
	NIF_T(TaggedTypeData16)
	class CMyClassForGen2_0
	{
		NIF_T(TaggedTypeData17)
		class CMyClassForGen2_0_0
		{
		public:
			NIF_F(FieldData36)
			float m_member2_0_0_Float_0;
		};
	public:
		NIF_F(FieldData37)
		float m_member2_0_Float_0;
		NIF_F(FieldData38)
		float m_member2_0_Float_1;
		NIF_F(FieldData39)
		EMyEnumOptionStyle m_member2_0_enum_2;
	};
}

namespace TestTypesScope0ForGen
{
	namespace TestTypesScope1ForGen
	{
		NIF_T(TaggedTypeData28)
		class CMyClassForGen2_1
		{
		public:
			NIF_F(FieldData40)
			bool m_member2_1_Bool_0;
			NIF_F(FieldData41)
			float m_member2_1_Float_1;
			NIF_F(FieldData42)
			bool m_member2_1_Bool_2;
		};
	}
}