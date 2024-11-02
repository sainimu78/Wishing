#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define LABEL_0 "Type"
#define LABEL_1 "InfoType"
#define LABEL_2 "GetType"
#define LABEL_3 "BaseType"

	namespace HardCodedTemplate
	{
		static const char* GetTypeCode = 
"StaticGetType<" MAKELABEL(LABEL_0) ">()";
		static const char* CastGetTypeCode = 
"" MAKELABEL(LABEL_1) "::Cast(StaticGetType<" MAKELABEL(LABEL_0) ">())";
		static const char* InitTypeCode =
"auto type = " MAKELABEL(LABEL_2) R"(;
type->InitInheritableTypeMeta(CInheritableType::Cast(StaticGetType<)" MAKELABEL(LABEL_3) ">()));";
	}
}