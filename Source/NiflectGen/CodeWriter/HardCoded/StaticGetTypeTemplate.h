#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define LABEL_0 "Include"
#define LABEL_1 "TypeDecl"
#define LABEL_2 "StaticGetTypeDecl"
#define LABEL_3 "Impl"

	namespace HardCodedTemplate
	{
		static const char* GenH =
R"(#pragma once
)" MAKELABEL(LABEL_0) R"(

)" MAKELABEL(LABEL_1) R"(

namespace Niflect
{
	)" MAKELABEL(LABEL_2) R"(
})";
		static const char* GenCpp =
"" MAKELABEL(LABEL_0) R"(

namespace Niflect
{
	)" MAKELABEL(LABEL_3) R"(
})";
	}
}