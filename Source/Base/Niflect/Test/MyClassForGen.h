#pragma once
#include "Niflect/Base/NiflectMacro.h"
#include "Niflect/Base/NiflectBase.h"
//
//namespace MyTestNamespace0
//{
//	namespace MyTestNamespace1
//	{
//		NIF_T(MyTypeData0)
//		class CMyScopeOnly
//		{
//		public:
//			NIF_T(MyTypeData0)
//			class CMyClassScoped0
//			{
//			public:
//				CMyClassScoped0()
//					: m_bool_0(false)
//					, m_float_1(123.321f)
//				{
//				}
//				NIF_F(MyFieldData0)
//				bool m_bool_0;
//				NIF_F(MyFieldData1)
//				float m_float_1;
//			};
//		};
//	}
//}

namespace MyTestClassScope
{
	NIF_T(MyTypeData0)
	class CMyClass0
	{
	public:
		CMyClass0()
			: m_bool_0(false)
			, m_float_1(123.321f)
		{
		}
		NIF_F(MyFieldData0)
		bool m_bool_0;
		NIF_F(MyFieldData1)
		float m_float_1;
	};
	//
	//NIF_T(MyTypeData1)
	//class CMyClassBase0
	//{
	//public:
	//	CMyClassBase0()
	//		: m_base_float_1(123.321f)
	//		, m_base_float_2(123.321f)
	//	{
	//	}
	//	NIF_F(MyFieldData2)
	//	Niflect::CString m_base_str_0;
	//	bool MyFunc0(float arg0, const CMyClass0& arg1, bool* arg2, CMyClass0* arg3, float** arg4)
	//	{
	//		printf("Invoke MyFunc0: %f, %f, %s, %f, %f\n", arg0, arg1.m_float_1, *arg2 ? "true" : "false", arg3->m_float_1, arg4[1][2]);
	//		if ((arg0 == 1.0f) &&
	//			(arg1.m_float_1 == 123.321f) &&
	//			(*arg2 == true) &&
	//			(arg3->m_float_1 == 2.0f) &&
	//			(arg4[1][2] == 9.0f)
	//			)
	//		{
	//			return true;
	//		}
	//		return false;
	//	}
	//	NIF_F(MyFieldData3)
	//	float m_base_float_1;
	//	NIF_F(MyFieldData4)
	//	float m_base_float_2;
	//};
	//
	//NIF_T(MyTypeData2)
	//enum class EMyEnum_OptionStyle
	//{
	//	None NIF_C(MyEnumConstData0),
	//	Option0 NIF_C(MyEnumConstData1),
	//	Option1,
	//	Option2 NIF_C(MyEnumConstData3),
	//};
	//
	//NIF_T(MyTypeData3)
	//class CMyClass1 : public CMyClassBase0
	//{
	//public:
	//	CMyClass1()
	//		: m_float_0(123.321f)
	//		, m_float_3(123.321f)
	//		, m_float_5(123.321f)
	//	{
	//	}
	//	NIF_F(MyFieldData5)
	//	float m_float_0;
	//	NIF_F(MyFieldData6)
	//	CMyClass0 m_obj_1;
	//	NIF_F(MyFieldData7)
	//	Niflect::TArrayNif<float> m_array_2;
	//	NIF_F(MyFieldData8)
	//	float m_float_3;
	//	NIF_F(MyFieldData9)
	//	Niflect::TArrayNif<CMyClass0> m_array_4;
	//	NIF_F(MyFieldData10)
	//	float m_float_5;
	//	NIF_F(MyFieldData11)
	//	Niflect::TArrayNif<Niflect::TArrayNif<float> > m_array_6;
	//};


	//namespace DDDDD
	//{
	//	class TSSSSSS
	//	{
	//	public:
	//		using MyString = Niflect::CString;
	//	};
	//}

	//using namespace DDDDD;
	
	//NIF_T(MyTypeData0)
	//class CMyScopeOnly1
	//{
	//public:
	//	NIF_T(MyTypeData0)
	//	class CMyClassScoped1
	//	{
	//	public:
	//		CMyClassScoped1()
	//			: m_bool_0(false)
	//			, m_float_1(123.321f)
	//		{
	//		}
	//		NIF_F(MyFieldData0)
	//		bool m_bool_0;
	//		NIF_F(MyFieldData1)
	//		float m_float_1;
	//	};
	//};

	NIF_T(MyTypeData3)
	class CMyClass1 : public CMyClass0
	{
	public:
		NIF_F(MyFieldData6)
		Niflect::CString m_base_str_0;
		NIF_F(MyFieldData7)
		Niflect::TArrayNif<float> m_array_1;
		
		NIF_F(MyFieldData8)
		Niflect::TMap<Niflect::CString, float> m_map_2;
		//NIF_F(MyFieldData8)
		//Niflect::TMap<Niflect::CString, MyTestNamespace0::MyTestNamespace1::CMyScopeOnly> m_map_2;
		//NIF_F(MyFieldData8)
		//Niflect::TMap<Niflect::CString, Niflect::TArrayNif<float> > m_map_2;

		//NIF_F(MyFieldData9)
		//Niflect::TArrayNif<MyTestNamespace0::MyTestNamespace1::CMyScopeOnly> m_array_3;

		//NIF_F(MyFieldData10)
		//MyTestNamespace0::MyTestNamespace1::CMyScopeOnly m_sub_4;
		//NIF_F(MyFieldData10)
		//CMyClass0 m_sub_4;
		//NIF_F(MyFieldData10)
		//MyTestNamespace0::MyTestNamespace1::CMyScopeOnly::CMyClassScoped0 m_sub_4;
		//NIF_F(MyFieldData10)
		//CMyScopeOnly1::CMyClassScoped1 m_sub_4;
	};
}