#pragma once
#include "Nata/ExampleNata.h"
#include "Example0_gen.h"

NIF_T(CExampleNata())
class CExample0
{
	NIFGNSD()
public:
	CExample0();

private:
	NIF_F()
	float m_value;
};