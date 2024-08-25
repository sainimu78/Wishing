#pragma once
#include "Niflect/NiflectMacro.h"
//#include <vector>
//#include "Niflect/NiflectBase.h"

namespace Engine
{
	NIF_T()
	class CEngineObject
	{
	public:
		CEngineObject()
			: m_float_0(0.0f)
			, m_bool_1(false)
		{

		}

	public:
		void InitForTest()
		{
			m_float_0 = 1.23f;
			m_bool_1 = true;
		}
		bool operator==(const CEngineObject& rhs) const
		{
			return m_float_0 == rhs.m_float_0
				&& m_bool_1 == rhs.m_bool_1
				;
		}

	public:
		NIF_F()
		float m_float_0;
		NIF_F()
		bool m_bool_1;
	};

	//NIF_T()
	//class CEngineObject
	//{
	//public:
	//	CEngineObject();

	//public:
	//	void InitForTest()
	//	{
	//	}
	//	bool operator==(const CEngineObject& rhs) const
	//	{
	//		return false;
	//	}

	//public:
	//	//NIF_F()
	//	//Niflect::TArrayNif<float> m_array_float_0;
	//	//NIF_F()
	//	//std::vector<bool> m_array_bool_1;
	//	//NIF_F()
	//	//Niflect::TMap<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> > > m_map_string_float_2;
	//	//NIF_F()
	//	//Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> > m_map_string_float_2;
	//	NIF_F()
	//	Niflect::TMap<Niflect::CString, float> m_map_string_float_2;
	//};
}