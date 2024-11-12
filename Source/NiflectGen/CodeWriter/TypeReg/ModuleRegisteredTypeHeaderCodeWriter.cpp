#include "NiflectGen/CodeWriter/TypeReg/ModuleRegisteredTypeHeaderCodeWriter.h"
#include "NiflectGen/CodeWriter/HardCoded/HardCodedTemplate.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/CppWriter.h"

namespace NiflectGen
{
	namespace HardCodedTemplate
	{
#define LABEL_0 "Include"
#define LABEL_1 "Prefix"

		constexpr const char* ModuleRegisteredTypeHeader =
R"(#pragma once
)" MAKELABEL(LABEL_0) R"(

namespace Niflect
{
	template <typename T>
	class )" MAKELABEL(LABEL_1) R"(TRegisteredType
	{
	public:
		static bool IsValid()
		{
			return s_type != NULL;
		}

		static CNiflectType* s_type;
	};

	template <typename T>
	CNiflectType* )" MAKELABEL(LABEL_1) R"(TRegisteredType<T>::s_type = NULL;

	template <typename T>
	CNiflectType* )" MAKELABEL(LABEL_1) R"(StaticGetType()
	{
		return )" MAKELABEL(LABEL_1) R"(TRegisteredType<T>::s_type;
	}

	template <typename T>
	CSharedAccessor )" MAKELABEL(LABEL_1) R"(CreateTypeAccessor();

	template <typename TType, typename TInfo = CNiflectType>
	static void )" MAKELABEL(LABEL_1) R"(RegisterType(CNiflectTable* table, const Niflect::CString& id, const CreateTypeAccessorFunc& Func)
	{
		CTypeInvokations typeFuncs;
		typeFuncs.m_InvokeConstructorFunc = &GenericInstanceInvokeConstructor<TType>;
		typeFuncs.m_InvokeDestructorFunc = &GenericInstanceInvokeDestructor<TType>;
		typeFuncs.m_CreateTypeAccessorFunc = Func;

		auto shared = Niflect::MakeShared<TInfo>();
		CNiflectType* type = shared.Get();
		auto idx = table->AddType(shared);
		ASSERT(!)" MAKELABEL(LABEL_1) R"(TRegisteredType<TType>::IsValid());
		type->InitTypeMeta2(sizeof(TType), CNiflectType::GetTypeHash<TType>(), idx, typeFuncs, id, &)" MAKELABEL(LABEL_1) R"(TRegisteredType<TType>::s_type);
		ASSERT()" MAKELABEL(LABEL_1) R"(TRegisteredType<TType>::IsValid());
	}
})";
	}

	void WriteModuleRegisteredTypeHeaderCodeWriter(const SModuleRegisteredTypeHeaderWritingContext& context, SModuleRegisteredTypeHeaderGenData& data)
	{
		CCodeTemplate tpl1;
		tpl1.ReadFromRawData(HardCodedTemplate::ModuleRegisteredTypeHeader);
		CLabelToCodeMapping map;

		CCodeLines linesInclude;
		{
			Niflect::TArrayNif<CHeaderFilePathData> vecHeaderData;
			vecHeaderData.push_back(NiflectGenDefinition::NiflectFramework::FilePath::NiflectTableHeader);
			CIncludesHelper::ConvertFromHeaderFilePaths(vecHeaderData, context.m_moduleRegInfo.m_writingHeaderSearchPaths, linesInclude);
			//linesCppInclude = linesFilePath;
		}
		MapLabelToLines(map, LABEL_0, linesInclude);
		MapLabelToText(map, LABEL_1, context.m_moduleRegInfo.m_moduleScopeSymbolPrefix);
		Niflect::TSet<Niflect::CString> setReplacedLabel;
		tpl1.ReplaceLabels(map, data.m_linesHeader, &setReplacedLabel);
	}
}