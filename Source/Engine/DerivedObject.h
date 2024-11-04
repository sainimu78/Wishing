#pragma once
#include "Engine/EngineObject.h"
#include "Engine/DerivedObject_gen.h"

namespace Engine
{
	NIF_T()
	class CDerivedObject : public CEngineObject
	{
		GENERATED_BODY()
		typedef CEngineObject inherited;
	public:
		CDerivedObject()
			: m_derived_bool_1(false)
			, m_derived_float_2(0.0f)
		{
		}
		void InitForTest()
		{
			inherited::InitForTest();
			m_derived_string_0 = "derived nihao";
			m_derived_bool_1 = true;
			m_derived_float_2 = 11.0f;
		}
		bool operator==(const CDerivedObject& rhs) const
		{
			return inherited::operator==(rhs)
				&& m_derived_string_0 == rhs.m_derived_string_0
				&& m_derived_bool_1 == rhs.m_derived_bool_1
				&& m_derived_float_2 == rhs.m_derived_float_2
				;
		}
	public:
		NIF_F()
		Niflect::CString m_derived_string_0;
		NIF_F()
		bool m_derived_bool_1;
		NIF_F()
		float m_derived_float_2;
	};

	//NIF_T()
	//struct SBase
	//{
	//	NIF_F()
	//	float m_float_0;
	//};

	//NIF_T()
	//struct SDerived : SBase
	//{
	//	NIF_F()
	//	Niflect::CString m_derived_0;
	//};
}