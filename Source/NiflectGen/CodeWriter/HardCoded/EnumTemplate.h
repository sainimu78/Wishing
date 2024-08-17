#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
	namespace HardCodedTemplate
	{
		static const char* TypeRegPrivate =
R"()"
;
		static const char* TypeRegClassScopeName_Enum =
"CEnumReg_" MAKELABEL(LABEL_SHARED_3)
;
	}
}