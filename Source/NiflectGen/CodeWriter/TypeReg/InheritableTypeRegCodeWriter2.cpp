#include "NiflectGen/CodeWriter/TypeReg/InheritableTypeRegCodeWriter2.h"
#include "NiflectGen/util/CursorUtil.h"
#include "NiflectGen/CodeWriter/HardCoded/InheritableTypeTemplate.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Util/TypeUtil.h"

namespace NiflectGen
{
	CInheritableTypeRegCodeWriter2::CInheritableTypeRegCodeWriter2(const Niflect::TArrayNif<CResolvedCursorNode>& vecMemberIndexedRoot, const Niflect::TArrayNif<CTaggedInheritableTypeMember*>& vecMember, const CTaggedType* baseTaggedType)
		: m_vecMemberIndexedRoot(vecMemberIndexedRoot)
		, m_vecMember(vecMember)
		, m_baseTaggedType(baseTaggedType)
	{

	}
	void CInheritableTypeRegCodeWriter2::WriteResocursorNodeBodyCode(CCodeLines& linesResoBodyCode) const
	{
		//linesResoBodyCode.push_back(NiflectUtil::FormatString("My Name: %s", m_bindingTypeIndexedRoot->m_resocursorName.c_str()));
		ASSERT(m_bindingTypeIndexedRoot->m_accessorBindingIndex);

		{
			linesResoBodyCode.push_back("---------------");
			for (uint32 idx = 0; idx < m_vecMemberIndexedRoot.size(); ++idx)
			{
				auto& itA = m_vecMemberIndexedRoot[idx];
				auto& a = itA.m_resocursorName;
				auto& itB = m_vecMember[idx];
				auto b = CXStringToCString(clang_getCursorSpelling(itB->GetCursor()));
				auto c = NiflectUtil::FormatString("%s %s;", a.c_str(), b.c_str());
				linesResoBodyCode.push_back(c);
			}
			//setting.GetBindingTypeDecl().m_cursorDecl
		}
	}
	void CInheritableTypeRegCodeWriter2::CollectDependencyHeaderFilePaths(CDependencyHeaderFilePathRefs& dependencyHeaderFilePathRefs) const
	{
		//还差基类的include
		ASSERT(m_bindingTypeIndexedRoot->m_vecRequiredHeaderFilePath.size() == 1);
		dependencyHeaderFilePathRefs.m_vecDecl.push_back(&m_bindingTypeIndexedRoot->m_vecRequiredHeaderFilePath[0]);
		for (auto& it0 : m_vecMemberIndexedRoot)
		{
			for (auto& it1 : it0.m_vecRequiredHeaderFilePath)
				dependencyHeaderFilePathRefs.m_vecImpl.push_back(&it1);
		}
	}
	void CInheritableTypeRegCodeWriter2::WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const
	{
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(BBBBBBBB<${Nihao}>)"
;
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			data.m_fieldLayoutFuncName = ReplaceLabelToText1(aaaaaaaaaaaaaaaaa, "Nihao", m_bindingTypeIndexedRoot->m_resocursorName);
		}
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(table->RegisterType<${Nihao}>("${Nihao}", &${Bucuo});)"
;
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			CLabelToCodeMapping map;
			MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot->m_resocursorName);
			MapLabelToText(map, "Bucuo", data.m_fieldLayoutFuncName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, data.m_linesInvokeRegisterType, &setReplacedLabel);
		}
		Niflect::CString funcSignature;
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(void ${Bucuo}();)"
;
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			funcSignature = ReplaceLabelToText1(aaaaaaaaaaaaaaaaa, "Bucuo", data.m_fieldLayoutFuncName);
		}
		{
			data.m_linesCreateFieldLayoutOfTypeDecl.push_back(funcSignature);
		}
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(void ${Bucuo}()
{
	${Shima}
})"
;
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			CLabelToCodeMapping map;
			MapLabelToText(map, "Bucuo", data.m_fieldLayoutFuncName);
			CCodeLines linesMembers;
			for (auto& it : m_vecMemberIndexedRoot)
				linesMembers.push_back(it.m_resocursorName);
			MapLabelToLines(map, "Shima", linesMembers);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, data.m_linesCreateFieldLayoutOfTypeImpl, &setReplacedLabel);
		}
	}
	void CInheritableTypeRegCodeWriter2::WriteStaticRegisterType(const STypeRegClassWritingContext& context, CCodeLines& lines) const
	{
		static const char* aaaaaaaaaaaaaaaaa =
R"(static void StaticRegisterType()
{
	${Bucuo}
})";
		CCodeTemplate tpl1;
		tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
		CLabelToCodeMapping map;
		MapLabelToLines(map, "Bucuo", context.m_linesRegisterType);
		Niflect::TSet<Niflect::CString> setReplacedLabel;
		tpl1.ReplaceLabels(map, lines, &setReplacedLabel);
	}
	void CInheritableTypeRegCodeWriter2::WriteStaticInitType(const STypeRegClassWritingContext& context, CCodeLines& lines) const
	{
		static const char* aaaaaaaaaaaaaaaaa =
R"(static void StaticInitType()
{
	auto type = (Cast)StaticGetType<${Nihao}>();
	type->InitInheritableTypeMeta(StaticGetType<${Bucuo}>);
})";
		if (m_baseTaggedType != NULL)
		{
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			CLabelToCodeMapping map;
			MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot->m_resocursorName);
			MapLabelToText(map, "Bucuo", m_baseTaggedType->m_taggedResoRoot.m_resocursorName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, lines, &setReplacedLabel);
		}
	}
	void CInheritableTypeRegCodeWriter2::Deprecated_WriteTypeRegClass(const STypeRegClassWritingContext& context, CTypeRegClassWritingData2& data) const
	{
		static const char* aaaaaaaaaaaaaaaaa =
R"(class CMyTypeReg_${Nihao}
{
public:
	${Shima}
	${Bucuo}
};)"
;
		CCodeTemplate tpl1;
		tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
		CLabelToCodeMapping map;
		MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot->m_resocursorName);
		CCodeLines linesStaticRegisterType;
		this->WriteStaticRegisterType(context, linesStaticRegisterType);
		MapLabelToLines(map, "Shima", linesStaticRegisterType);
		CCodeLines linesStaticInitType;
		this->WriteStaticInitType(context, linesStaticInitType);
		if (linesStaticInitType.size() > 0)
			MapLabelToLines(map, "Bucuo", linesStaticInitType);
		Niflect::TSet<Niflect::CString> setReplacedLabel;
		tpl1.ReplaceLabels(map, data.m_linesImpl, &setReplacedLabel);
	}
	void CInheritableTypeRegCodeWriter2::WriteInvokeInitType(const STypeRegClassWritingContext& context, CTypeRegTaggedTypeInitWritingData2& data) const
	{
		if (m_baseTaggedType != NULL)
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(auto type = (Cast)StaticGetType<${Nihao}>();
type->InitInheritableTypeMeta(StaticGetType<${Bucuo}>);)";
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			CLabelToCodeMapping map;
			MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot->m_resocursorName);
			MapLabelToText(map, "Bucuo", m_baseTaggedType->m_taggedResoRoot.m_resocursorName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, data.m_lines, &setReplacedLabel);
		}
	}
}