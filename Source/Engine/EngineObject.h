#pragma once
#include "Niflect/NiflectMacro.h"

namespace Engine
{
	NIF_T()
	class CEngineObject
	{
	public:
		CEngineObject();

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
}