#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define LABEL_0 "Includes"
#define LABEL_1 "TypeRegClassDefinitions"
#define LABEL_2 "TypeRegClassesNamespace"

	namespace HardCodedTemplate
	{
		static const char* TypeRegPrivateH =
R"(#pragma once
#include "Niflect/Type/NiflectTable.h"
)" MAKELABEL(LABEL_0) R"(

)" MAKELABEL(LABEL_1)
;
		static const char* TypeRegClassNamespaceScope =
"namespace " MAKELABEL(LABEL_2) R"(
{
	)" MAKELABEL(LABEL_1) R"(
})"
;
	}
}