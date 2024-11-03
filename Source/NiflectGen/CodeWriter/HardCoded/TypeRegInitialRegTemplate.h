#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define LABEL_0 "Type"
#define LABEL_1 "Info"
#define LABEL_2 "Func"
#define LABEL_3 "Body"
#define LABEL_4 "Accessor"
#define LABEL_5 "Nexts"
#define LABEL_6 "AccessorForm"
#define LABEL_7 "Offset"
#define LABEL_8 "FieldName"
#define LABEL_9 "TypeForLastTemplateArg"
#define LABEL_10 "API"
#define LABEL_11 "Namespace"
#define LABEL_12 "ScopedCode"

	namespace HardCodedTemplate
	{
		constexpr const char* CreateTypeAccessorFuncName =
R"(CreateTypeAccessor<)" MAKELABEL(LABEL_9) ">";
		constexpr const char* InvokeRegisterType =
R"(table->RegisterType2<)" MAKELABEL(LABEL_0) ", " MAKELABEL(LABEL_1) R"(>(")" MAKELABEL(LABEL_0) R"(", &)" MAKELABEL(LABEL_2) R"();)";
		constexpr const char* CreateTypeAccessorDecl =
R"(template <>
CSharedAccessor )" MAKELABEL(LABEL_2) "();";
		constexpr const char* CreateTypeAccessorImpl =
R"(template <>
CSharedAccessor )" MAKELABEL(LABEL_2) R"(()
{
	)" MAKELABEL(LABEL_3) R"(
})";
		constexpr const char* CreateAndInitTypeAccessor =
"auto node0 = Niflect::MakeShared<" MAKELABEL(LABEL_4) R"(>();
node0->InitType(Niflect::StaticGetType<)" MAKELABEL(LABEL_9)  R"(>());
)" MAKELABEL(LABEL_5) R"(
return node0;
)";
		constexpr const char* CreateAndInitNextsAccessor =
"auto type1 = Niflect::StaticGetType<" MAKELABEL(LABEL_9) R"(>();
auto node1 = type1->CreateAccessor();)";
	constexpr const char* InitChildAccessor =
R"(node1->InitForField(")" MAKELABEL(LABEL_0) R"(", )" MAKELABEL(LABEL_7) R"();
node0->AddChild(node1);)";
	constexpr const char* GetFieldOffset =
R"(Niflect::GetFieldOffset(&)" MAKELABEL(LABEL_0) "::" MAKELABEL(LABEL_8) R"())";
	constexpr const char* InitElementAccessor =
R"(node1->InitForElement();
node0->InitElementAccessor(node1);)";
	constexpr const char* StaticGetTypeFuncName =
R"(StaticGetType<)" MAKELABEL(LABEL_9) ">";
	constexpr const char* StaticGetTypeSpecDecl =
R"(template <>
)" MAKELABEL(LABEL_10) " CNiflectType* " MAKELABEL(LABEL_2) R"(();)";
	constexpr const char* StaticGetTypeSpecImpl =
R"(template <>
CNiflectType* )" MAKELABEL(LABEL_2) R"(()
{
	return TRegisteredType<)" MAKELABEL(LABEL_9) R"(>::s_type;
})";
	constexpr const char* NamespaceScopeCode =
"namespace " MAKELABEL(LABEL_11) R"(
{
	)" MAKELABEL(LABEL_12) R"(
}
)";
	}
}