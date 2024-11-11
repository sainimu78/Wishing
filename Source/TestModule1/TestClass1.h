#pragma once
#include "TestModule1/TestClass1_gen.h"

namespace TestModule1
{

	NIF_T()
	class CTestBase1
	{
		GENERATED_BODY()
	public:
		CTestBase1()
			: m_base_bool_1(false)
		{

		}
		void InitForTest()
		{
			m_base_string_0 = "base string 0";
			m_base_bool_1 = true;
			m_base_std_string_2 = "base std string 2";
		}
		bool operator==(const CTestBase1& rhs) const
		{
			return m_base_string_0 == rhs.m_base_string_0
				&& m_base_bool_1 == rhs.m_base_bool_1
				&& m_base_std_string_2 == rhs.m_base_std_string_2
				;
		}

	private:
		NIF_F()
		Niflect::CString m_base_string_0;
		NIF_F()
		bool m_base_bool_1;
		NIF_F()
		std::string m_base_std_string_2;
	};

	NIF_T()
	class CTestClass1 : public CTestBase1
	{
		GENERATED_BODY()
		typedef CTestBase1 inherited;
	public:
		void InitForTest()
		{
			inherited::InitForTest();
			m_std_string_0 = "std string 0";
		}
		bool operator==(const CTestClass1& rhs) const
		{
			return inherited::operator==(rhs)
				&& m_std_string_0 == rhs.m_std_string_0
				;
		}

	private:
		NIF_F()
		std::string m_std_string_0;
	};
}