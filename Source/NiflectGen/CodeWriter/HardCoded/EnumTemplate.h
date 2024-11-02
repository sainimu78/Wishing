#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
	namespace HardCodedTemplate
	{
#define LABEL_0 "Type"
#define LABEL_1 "AddConsts"
#define LABEL_2 "Const"

		constexpr const char* InitTypeCode =
R"(CEnumMeta enumMeta;
auto& vec = enumMeta.m_vecEnumConstant;
)" MAKELABEL(LABEL_1) R"(
auto et = CEnum::Cast(StaticGetType<)" MAKELABEL(LABEL_0) R"(>());
et->InitEnumMeta(enumMeta);
)";
		constexpr const char* AddEnumConsts =
R"(vec.push_back(")" MAKELABEL(LABEL_2) R"(");)";
	}
}