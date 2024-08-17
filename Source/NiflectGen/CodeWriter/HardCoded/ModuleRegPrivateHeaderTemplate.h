#pragma once
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"

namespace NiflectGen
{
#define LABEL_1 "TypeRegsAddAndInitTable"
#define LABEL_2 "InvokationRegisterTypes"
#define LABEL_3 "InvokationInitTypes"
//#define LABEL_4 "TypeRegsInitMethod"
#define LABEL_7 "IncludesTypeRegPrivateHeader"
//#define LABEL_8 "ModuleCodeUnique"
//#define LABEL_9 "ModuleRegSplittedID"
//#define LABEL_10 "ModuleRegClassName"
//#define LABEL_11 "IncludesSplittedModuleRegPrivateHeader"

	namespace HardCodedTemplate
	{
//		static const char* ModuleRegClassName =
//"CModuleReg_" MAKELABEL(LABEL_0) MAKELABEL(LABEL_9)
//;
		static const char* ModuleRegPrivateH =
R"(#pragma once
#include "Niflect/Type/NiflectRegistration.h"
)" MAKELABEL(LABEL_7) R"(

namespace NiflectModuleReg
{
	using namespace Niflect;
	
	class CModuleReg_)" MAKELABEL(LABEL_SHARED_0) R"( : public CNiflectRegistration
	{
	protected:
		virtual void DoInitTables() override
		{
			)" MAKELABEL(LABEL_1) R"(
		}
		virtual void DoRegisterTypes() override
		{
			)" MAKELABEL(LABEL_2) R"(
		}
		virtual void DoInitTypes() const override
		{
			)" MAKELABEL(LABEL_3) R"(
		}
	};

	static void CreateModuleRegistration()
	{
		CNiflectRegistration::StaticCreate<CModuleReg_)" MAKELABEL(LABEL_SHARED_0) R"(>();
	}
	static void DestroyModuleRegistration()
	{
		CNiflectRegistration::StaticDestroy();
	}
}

namespace Niflect
{
	CSharedRegistration CNiflectRegistration::s_reg;
}

Niflect::CNiflectRegistration* GetNiflectModuleRegistration()
{
	return Niflect::CNiflectRegistration::StaticGet();
})"
;
//		static const char* ModuleReg_TypeRegInitTable =
//R"({
//	auto table = this->AddNewTable();
//	table->Init(CString());
//})"
//;
//	static const char* ModuleReg_CodeUnique = 
//R"()"
//;
	}
}