#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define LABEL_0 "Include"
#define LABEL_1 "RegisterTypes"
#define LABEL_2 "InitTypes"
//#define LABEL_3 "StaticModuleReg"
#define LABEL_4 "ModuleName"
#define LABEL_5 "ModuleAPI"
#define LABEL_6 "GetModuleC"

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
		static const char* StaticModuleRegHeader =
R"(#pragma once
)" MAKELABEL(LABEL_0) R"(

)" MAKELABEL(LABEL_5) R"( Niflect::CNiflectModule* GetModule_)" MAKELABEL(LABEL_4) "();";
		static const char* StaticModuleRegImpl =
R"(namespace Niflect
{
	class CRegger_)" MAKELABEL(LABEL_4) R"(
	{
	public:
		CRegger_)" MAKELABEL(LABEL_4) R"((const Niflect::CString& name, const ModuleRegisterTypesFunc& RegisterTypesFunc, const ModuleInitTypesFunc& InitTypesFunc)
		{
			s_module = Niflect::MakeShared<CNiflectModule>();
			s_module->InitMeta(name, RegisterTypesFunc, InitTypesFunc);
		}
		static CSharedModule s_module;
	};
	CSharedModule CRegger_)" MAKELABEL(LABEL_4) R"(::s_module;
	static CRegger_)" MAKELABEL(LABEL_4) R"( g_staticRegger_)" MAKELABEL(LABEL_4) R"((")" MAKELABEL(LABEL_4) R"(", &GeneratedInitialReg, &GeneratedInitTypes);
}
Niflect::CNiflectModule* GetModule_)" MAKELABEL(LABEL_4) R"(()
{
	return Niflect::CRegger_)" MAKELABEL(LABEL_4) R"(::s_module.Get();
})";
		static const char* StaticModuleRegGetModuleC =
R"(extern "C" )" MAKELABEL(LABEL_5) R"( Niflect::CNiflectModule* )" MAKELABEL(LABEL_6) R"(()
{
	return GetModule_)" MAKELABEL(LABEL_4) R"(();
})";
	}
}