#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define LABEL_0 "Type"
#define LABEL_1 "Info"
#define LABEL_2 "Func"
#define LABEL_3 "Body"

	namespace HardCodedTemplate
	{
		constexpr const char* CreateFieldLayuotOfTypeFuncName = 
R"(CreateFieldLayoutOfType<)" MAKELABEL(LABEL_0) ">";
		constexpr const char* InvokeRegisterType =
R"(this->RegisterType2<)" MAKELABEL(LABEL_0) ", " MAKELABEL(LABEL_1) R"(>(")" MAKELABEL(LABEL_0) R"(", &)" MAKELABEL(LABEL_2) R"())";
		constexpr const char* CreateFieldLayoutOfTypeDecl =
"CSharedAccessor " MAKELABEL(LABEL_2) "(); ";
		constexpr const char* CreateFieldLayoutOfTypeImpl =
"CSharedAccessor " MAKELABEL(LABEL_2) R"(()
{
	)" MAKELABEL(LABEL_3) R"(
})";
	}
}