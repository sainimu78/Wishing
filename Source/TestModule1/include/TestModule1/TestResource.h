#pragma once
#include "Niflect/Base/SharedPtr.h"
#include "Niflect/Base/String.h"
#include "Niflect/NiflectMacro.h"
#include "TestModule1/TestResource_gen.h"

namespace TestModule1
{
	class CTestResource
	{
	public:
		CTestResource()
			: m_data_float_0(0.0f)
		{
		}
		void InitForTest(const Niflect::CString& path)
		{
			m_path = path;
			m_data_float_0 = 12.3f;
		}
		Niflect::CString m_path;
		float m_data_float_0;
	};
	using CSharedTestResource = Niflect::TSharedPtr<CTestResource>;

	template <typename TResource>
	class TTestResourcePointer
	{
	public:
		TTestResourcePointer()
			: m_p(NULL)
		{
		}
		TTestResourcePointer(TResource* p)
			: m_p(p)
		{
		}
		bool operator==(const TTestResourcePointer& rhs) const
		{
			return m_p == rhs.m_p;
		}
		TResource* m_p;
	};

	NIF_T()
	class CTestMyInstance
	{
		GENERATED_BODY()
	public:
		CTestMyInstance()
			: m_float_0(0.0f)
		{
		}
		void InitForTest()
		{
			m_float_0 = 12.3f;
		}
		bool operator==(const CTestMyInstance& rhs) const
		{
			return
				m_float_0 == rhs.m_float_0
				;
		}
		NIF_F()
		float m_float_0;
	};
	using CSharedTestMyInstance = Niflect::TSharedPtr<CTestMyInstance>;
}