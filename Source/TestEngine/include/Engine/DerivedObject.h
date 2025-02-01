#pragma once
#include "Engine/EngineObject.h"
#include "TestModule1/TestClass1.h"
#include "TestModule1/TestResourceFactory.h"
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
			, m_my_record_6{}
		{
		}
		void InitForTest()
		{
			inherited::InitForTest();
			m_derived_string_0 = "derived nihao";
			m_derived_bool_1 = true;
			m_derived_float_2 = 11.0f;
			m_derived_std_string_3 = "derived std string 3";
			m_test_class_4.InitForTest();
			m_array_test_base_5.resize(2);
			for (auto& it : m_array_test_base_5)
				it.InitForTest();
			TestModule1::InitForTest_SMyRecord(m_my_record_6);
		}
		bool operator==(const CDerivedObject& rhs) const
		{
			return inherited::operator==(rhs)
				&& m_derived_string_0 == rhs.m_derived_string_0
				&& m_derived_bool_1 == rhs.m_derived_bool_1
				&& m_derived_float_2 == rhs.m_derived_float_2
				&& m_derived_std_string_3 == rhs.m_derived_std_string_3
				&& m_test_class_4 == rhs.m_test_class_4
				&& m_array_test_base_5 == rhs.m_array_test_base_5
				&& m_my_record_6 == rhs.m_my_record_6
				;
		}
	public:
		NIF_F()
		Niflect::CString m_derived_string_0;
		NIF_F()
		bool m_derived_bool_1;
		NIF_F()
		float m_derived_float_2;
		NIF_F()
		std::string m_derived_std_string_3;
		NIF_F()
		TestModule1::CTestClass1 m_test_class_4;
		NIF_F()
		Niflect::TArray<TestModule1::CTestBase1> m_array_test_base_5;
		NIF_F()
		TestModule1::SMyRecord m_my_record_6;
	};

	using namespace TestModule1;

	NIF_T()
	class CDerivedFromModule1 : public TestModule1::CTestClass1
	{
		GENERATED_BODY()
		typedef TestModule1::CTestClass1 inherited;
	public:
		CDerivedFromModule1()
			: m_derived_bool_1(false)
			, m_derived_resource_4(NULL)
		{

		}
	public:
		void InitForTest()
		{
			inherited::InitForTest();
			m_derived_array_float_0.resize(3);
			m_derived_array_float_0[0] = 1.0f;
			m_derived_array_float_0[1] = 1.1f;
			m_derived_array_float_0[2] = 1.2f;
			m_derived_bool_1 = true;
			m_derived_string_2 = "derived string 2";
			auto fac = TestModule1::GetTestResourceFactory();
			m_derived_array_resource_3.resize(2);
			m_derived_array_resource_3[0] = fac->FindOrAdd("Nihao/a.txt");
			m_derived_array_resource_3[1] = fac->FindOrAdd("Bucuo/b.jpg");
			m_derived_resource_4 = fac->FindOrAdd("Shima/c.jpg");
		}
		bool operator==(const CDerivedFromModule1& rhs) const
		{
			return inherited::operator==(rhs)
				&& m_derived_array_float_0 == rhs.m_derived_array_float_0
				&& m_derived_bool_1 == rhs.m_derived_bool_1
				&& m_derived_string_2 == rhs.m_derived_string_2
				&& m_derived_array_resource_3 == rhs.m_derived_array_resource_3
				&& m_derived_resource_4 == rhs.m_derived_resource_4
				;
		}

	private:
		NIF_F()
		Niflect::TArray<float> m_derived_array_float_0;
		NIF_F()
		bool m_derived_bool_1;
		NIF_F()
		Niflect::CString m_derived_string_2;
		NIF_F()
		Niflect::TArray<CTestResource*> m_derived_array_resource_3;
		NIF_F()
		CTestResource* m_derived_resource_4;
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