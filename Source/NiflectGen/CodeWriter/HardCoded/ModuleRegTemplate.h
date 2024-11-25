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

namespace Niflect
{
	static void GeneratedInitialReg(Niflect::CNiflectTable* table)
	{
		)" MAKELABEL(LABEL_1) R"(
	}
	static void GeneratedInitTypes()
	{
		)" MAKELABEL(LABEL_2) R"(
	}
})";
	}
}