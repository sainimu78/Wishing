#pragma once
#include "Engine/EngineObject.h"

namespace Engine
{
	NIF_T()
	class CDerivedObject : public CEngineObject
	{
		typedef CEngineObject inherited;
	public:
		void InitForTest()
		{
			inherited::InitForTest();
			m_derived_string_0 = "derived nihao";
		}
		bool operator==(const CDerivedObject& rhs) const
		{
			return inherited::operator==(rhs)
				&& m_derived_string_0 == rhs.m_derived_string_0
				;
		}
	public:
		NIF_F()
		Niflect::CString m_derived_string_0;
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