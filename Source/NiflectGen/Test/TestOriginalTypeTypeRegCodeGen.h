#pragma once
#include "Niflect/NiflectMacro.h"
#include "Niflect/NiflectBase.h"
#include "Engine/Test/TestMyTransform.h"
#include "NiflectGen/Test/TestSomeTypes.h"//º¬TaggedTypeµÄ¶àÓàinclude

namespace TestMyFinding
{
	using namespace Niflect;

	NIF_T()
	enum class EMyOption
	{
		EDefaultMode NIF_C(),
		EMode0 NIF_C(),
		EState0 NIF_C(),
	};

	NIF_T()
	class CMyClass_0
	{
	public:
		CMyClass_0()
			: m_int32_1(0)
			, m_ec_opt_2(EMyOption::EDefaultMode)
		{

		}

		NIF_F()
		int32 m_int32_1;
		NIF_F()
		EMyOption m_ec_opt_2;
		NIF_F()
		TestAccessor2::TMyTransform<float> m_tm_3;
		NIF_F()
		std::pair<CString, float> m_pair_string_float_4;
		//NIF_F()
		//TestSomeScope::SMyStruct m_my_struct_5;
		NIF_F()
		Niflect::TArrayNif<float> m_array_float_6;
	};
}