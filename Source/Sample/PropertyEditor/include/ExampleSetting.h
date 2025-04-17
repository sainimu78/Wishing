#pragma once
#include "ExampleSetting_gen.h"

NIF_T()
class CExampleSetting
{
	NIFGNSD()
public:
	CExampleSetting();

private:
	NIF_F()
	float m_value;
};