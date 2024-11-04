#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define LABEL_0 "Include"
#define LABEL_1 "TypeDecl"
#define LABEL_2 "StaticGetTypeDecl"
#define LABEL_3 "Impl"
#define LABEL_4 "FileID"
#define LABEL_6 "Macros"
#define LABEL_9 "MacroDefinitionItems"
#define LABEL_10 "MacroDefinitionRoot"

	namespace HardCodedTemplate
	{
		static const char* LineNumberMacros =
"" MAKELABEL(LABEL_9) R"(

)" MAKELABEL(LABEL_10) R"(
)";
		static const char* GenH =
R"(#pragma once
#include "Niflect/NiflectMacro.h"
)" MAKELABEL(LABEL_0) R"(

)" MAKELABEL(LABEL_1) R"(

namespace Niflect
{
	)" MAKELABEL(LABEL_2) R"(
}

)" MAKELABEL(LABEL_6) R"(

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID )" MAKELABEL(LABEL_4) R"(

)";
		static const char* GenCpp =
"" MAKELABEL(LABEL_0) R"(

namespace Niflect
{
	)" MAKELABEL(LABEL_3) R"(
})";
	}
}