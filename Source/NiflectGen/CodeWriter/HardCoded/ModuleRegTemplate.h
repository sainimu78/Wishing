#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define LABEL_0 "Include"
#define LABEL_1 "RegisterTypes"
#define LABEL_2 "InitTypes"

	namespace HardCodedTemplate
	{
		static const char* ModuleRegImpl =
"" MAKELABEL(LABEL_0) R"(

void GeneratedNiflectRegistrationInitialReg()
{
	)" MAKELABEL(LABEL_1) R"(
}
void GeneratedNiflectRegistrationInitTypes()
{
	)" MAKELABEL(LABEL_2) R"(
})";
	}
}