#pragma once
#include "SampleObject_gen.h"

NIF_T()
class CSampleObject
{
	GENERATED_BODY()
public:
	CSampleObject()
		: m_value(0.0f)
	{
	}

public:
	void InitForTest()
	{
		m_value = 123.0f;
	}
	bool operator==(const CSampleObject& rhs) const
	{
		return m_value == rhs.m_value
			;
	}

private:
	NIF_F()
	float m_value;
};