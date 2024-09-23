#pragma once
#include "Niflect/NiflectMacro.h"
//#include <vector>
#include "Niflect/NiflectBase.h"

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
			m_string_2 = "nihao";
			m_std_string_3 = "std nihao";
			m_array_float_4.resize(2);
			m_array_float_4[0] = 2.0f;
			m_array_float_4[1] = 2.1f;
			m_std_array_float_5.resize(3);
			m_std_array_float_5[0] = 3.0f;
			m_std_array_float_5[1] = 3.1f;
			m_std_array_float_5[2] = 3.2f;
			m_array_array_float_6.resize(2);
			m_array_array_float_6[0].resize(3);
			m_array_array_float_6[0][0] = 4.0f;
			m_array_array_float_6[0][1] = 4.1f;
			m_array_array_float_6[0][2] = 4.2f;
			m_array_array_float_6[1].resize(2);
			m_array_array_float_6[1][0] = 4.3f;
			m_array_array_float_6[1][1] = 4.4f;
			m_bits_7.resize(3);
			m_bits_7[0] = true;
			m_bits_7[1] = false;
			m_bits_7[2] = true;
			m_array_bits_8.resize(2);
			m_array_bits_8[0].resize(2);
			m_array_bits_8[0][0] = true;
			m_array_bits_8[0][1] = false;
			m_array_bits_8[1].resize(3);
			m_array_bits_8[1][0] = true;
			m_array_bits_8[1][1] = false;
			m_array_bits_8[1][2] = true;
		}
		bool operator==(const CEngineObject& rhs) const
		{
			return m_float_0 == rhs.m_float_0
				&& m_bool_1 == rhs.m_bool_1
				&& m_string_2 == rhs.m_string_2
				&& m_std_string_3 == rhs.m_std_string_3
				&& m_array_float_4 == rhs.m_array_float_4
				&& m_std_array_float_5 == rhs.m_std_array_float_5
				&& m_array_array_float_6 == rhs.m_array_array_float_6
				&& m_bits_7 == rhs.m_bits_7
				&& m_array_bits_8 == rhs.m_array_bits_8
				;
		}

	public:
		//NIF_F()
		float m_float_0;
		//NIF_F()
		bool m_bool_1;
		//NIF_F()
		Niflect::CString m_string_2;
		//NIF_F()
		std::string m_std_string_3;
		//NIF_F()
		Niflect::TArrayNif<float> m_array_float_4;
		//NIF_F()
		std::vector<float> m_std_array_float_5;
		//NIF_F()
		Niflect::TArrayNif<Niflect::TArrayNif<float> > m_array_array_float_6;
		NIF_F()
		Niflect::TArrayNif<bool> m_bits_7;
		//NIF_F()
		Niflect::TArrayNif<Niflect::TArrayNif<bool> > m_array_bits_8;
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