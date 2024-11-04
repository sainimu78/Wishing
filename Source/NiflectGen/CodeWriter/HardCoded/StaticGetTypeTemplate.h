#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define MACRO_NAME_0 "GENERATED_BODY"
#define MACRO_NAME_1 "ExposeToAccessor"
#define LABEL_0 "Include"
#define LABEL_1 "TypeDecl"
#define LABEL_2 "StaticGetTypeDecl"
#define LABEL_3 "Impl"
#define LABEL_4 "FileID"
#define LABEL_5 "LineNum"
#define LABEL_6 "Macros"
#define LABEL_7 "MacroName"
#define LABEL_8 "MacroBody"
#define LABEL_9 "MacroDefinitionItems"
#define LABEL_10 "MacroDefinitionRoot"

	namespace HardCodedTemplate
	{
		static const char* LineNumberMacroGeneratedBody =
"" MAKELABEL(LABEL_4) "_" MAKELABEL(LABEL_5) "_" MACRO_NAME_0;
		static const char* LineNumberMacroExposeToAccessor = 
"" MAKELABEL(LABEL_4) "_" MAKELABEL(LABEL_5) "_" MACRO_NAME_1;
		static const char* LineNumberMacroDefinition =
R"(#define )" MAKELABEL(LABEL_7) R"(\
	)" MAKELABEL(LABEL_8);
		static const char* LineNumberMacroItem =
"" MAKELABEL(LABEL_7) R"(\)";
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