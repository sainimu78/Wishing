#pragma once
#include "TestModule1/TestModule1_gen.h"

namespace TestModule1
{
	NIF_T()
	class CTestClass1
	{
		GENERATED_BODY()
	public:
		void InitForTest()
		{
			m_std_string_0 = "std string 0";
		}
		bool operator==(const CTestClass1& rhs) const
		{
			return m_std_string_0 == rhs.m_std_string_0
				;
		}

	private:
		NIF_F()
		std::string m_std_string_0;
	};

	TESTMODULE1_API void TestModule1Create();
	TESTMODULE1_API void TestModule1Destroy();
}