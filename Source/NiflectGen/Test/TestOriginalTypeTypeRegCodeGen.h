#pragma once
#include "Niflect/NiflectMacro.h"
#include "Niflect/NiflectBase.h"
#include "Engine/Test/TestMyTransform.h"
#include "NiflectGen/Test/TestSomeTypes.h"

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
		TestSomeScope::SMyPairAlias<CString, float> m_my_pair_string_float_0;
		NIF_F()
		TestSomeScope::SMyPair<CString, float> m_my_pair_string_float_0_aaaaa;
		NIF_F()
		int32 m_int32_1;
		NIF_F()
		EMyOption m_ec_opt_2;
		NIF_F()
		TestAccessor2::TMyTransform<float> m_tm_3;
		NIF_F()
		std::pair<CString, float> m_pair_string_float_4;
	};
}