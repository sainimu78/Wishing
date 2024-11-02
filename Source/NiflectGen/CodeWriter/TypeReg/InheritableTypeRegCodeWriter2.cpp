#include "NiflectGen/CodeWriter/TypeReg/InheritableTypeRegCodeWriter2.h"
#include "NiflectGen/util/CursorUtil.h"
//#include "NiflectGen/CodeWriter/HardCoded/InheritableTypeTemplate.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Util/TypeUtil.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeAccessorCodeWriter.h"

namespace NiflectGen
{
	CInheritableTypeRegCodeWriter2::CInheritableTypeRegCodeWriter2(const Niflect::TArrayNif<CResolvedCursorNode>& vecFieldResocursorNode, const Niflect::TArrayNif<CTaggedInheritableTypeMember*>& vecField, const CTaggedType* baseTaggedType)
		: m_vecFieldResocursorNode(vecFieldResocursorNode)
		, m_vecField(vecField)
		, m_baseTaggedType(baseTaggedType)
	{

	}
	void CInheritableTypeRegCodeWriter2::WriteResocursorNodeBodyCode(CCodeLines& linesResoBodyCode) const
	{
		ASSERT(m_bindingTypeIndexedRoot->m_accessorBindingIndex);

		//{
		//	linesResoBodyCode.push_back("---------------");
		//	for (uint32 idx = 0; idx < m_vecMemberIndexedRoot.size(); ++idx)
		//	{
		//		auto& itA = m_vecMemberIndexedRoot[idx];
		//		auto& a = itA.m_resocursorName;
		//		auto& itB = m_vecMember[idx];
		//		auto b = CXStringToCString(clang_getCursorSpelling(itB->GetCursor()));
		//		auto c = NiflectUtil::FormatString("%s %s;", a.c_str(), b.c_str());
		//		linesResoBodyCode.push_back(c);
		//	}
		//}


		for (uint32 idx = 0; idx < m_vecFieldResocursorNode.size(); ++idx)
		{
			auto& itB = m_vecField[idx];
			auto fieldResocursorNameLastTemplateArg = m_vecFieldResocursorNode[idx].m_resocursorName;
			NiflectGenDefinition::CodeStyle::TryFormatNestedTemplate(fieldResocursorNameLastTemplateArg);
			auto fieldName = CXStringToCString(clang_getCursorSpelling(itB->GetCursor()));
			WriteNextInitChildAccessor(m_bindingTypeIndexedRoot->m_resocursorName, fieldResocursorNameLastTemplateArg, fieldName, linesResoBodyCode);
		}
	}
	void CInheritableTypeRegCodeWriter2::CollectDependencyHeaderFilePathAddrs(CDependencyHeaderFilePathAddrs& dependencyHeaderFilePathAddrs) const
	{
		//还差基类的include
		dependencyHeaderFilePathAddrs.m_vecDecl.push_back(m_bindingTypeIndexedRoot->GetHeaderFilePathAddrForTaggedType());
		for (auto& it0 : m_vecFieldResocursorNode)
			it0.GetHeaderFilePathAddrs(dependencyHeaderFilePathAddrs.m_vecImpl);
	}
	void CInheritableTypeRegCodeWriter2::WriteStaticInitType(const STypeRegClassWritingContext& context, CCodeLines& lines) const
	{
		if (m_baseTaggedType != NULL)
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(static void StaticInitType()
{
	auto type = (Cast)StaticGetType<${Nihao}>();
	type->InitInheritableTypeMeta(StaticGetType<${Bucuo}>);
})";
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			CLabelToCodeMapping map;
			MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot->m_resocursorName);
			MapLabelToText(map, "Bucuo", m_baseTaggedType->m_taggedResoRoot.m_resocursorName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, lines, &setReplacedLabel);
		}
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