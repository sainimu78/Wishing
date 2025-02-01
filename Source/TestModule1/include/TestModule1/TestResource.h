#pragma once
#include "Niflect/Base/SharedPtr.h"
#include "Niflect/Base/String.h"

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
}