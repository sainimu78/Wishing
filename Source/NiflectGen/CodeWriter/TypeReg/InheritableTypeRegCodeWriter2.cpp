#include "NiflectGen/CodeWriter/TypeReg/InheritableTypeRegCodeWriter2.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "NiflectGen/CodeWriter/HardCoded/InheritableTypeTemplate2.h"
#include "NiflectGen/CodeWriter/CppTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeAccessorCodeWriter.h"

namespace NiflectGen
{
	CInheritableTypeRegCodeWriter2::CInheritableTypeRegCodeWriter2(const Niflect::TArrayNif<CResolvedCursorNode>& vecFieldResocursorNode, const Niflect::TArrayNif<CTaggedInheritableTypeMember*>& vecField, const CTaggedType* baseTaggedType, uint32 generatedBodyLineNumber)
		: m_vecFieldResocursorNode(vecFieldResocursorNode)
		, m_vecField(vecField)
		, m_baseTaggedType(baseTaggedType)
		, m_generatedBodyLineNumber(generatedBodyLineNumber)
	{

	}
	void CInheritableTypeRegCodeWriter2::WriteResocursorNodeBodyCode(const SResocursorNodeBodyCodeWritingContext& context, CCodeLines& linesResoBodyCode) const
	{
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
			auto fieldName = CXStringToCString(clang_getCursorSpelling(itB->GetCursor()));
			auto fieldStaticGetTypeFuncName = m_vecFieldResocursorNode[idx].GetStaticGetTypeFuncName(context.m_moduleRegInfo.m_moduleScopeSymbolPrefix);
			CCodeLines linesNata;
			itB->WriteCopyNataCode(linesNata);
			WriteNextInitChildAccessor2(m_bindingTypeIndexedRoot->m_resocursorName, fieldStaticGetTypeFuncName, fieldName, linesNata, linesResoBodyCode);
		}
	}
	void CInheritableTypeRegCodeWriter2::CollectDependencyHeaderFilePathAddrs(CDependencyHeaderFilePathAddrs& dependencyHeaderFilePathAddrs) const
	{
		//还差基类的include
		dependencyHeaderFilePathAddrs.m_vecDecl.push_back(m_bindingTypeIndexedRoot->GetHeaderFilePathAddrForTaggedType());
		for (auto& it0 : m_vecFieldResocursorNode)
			it0.GetHeaderFilePathAddrs(dependencyHeaderFilePathAddrs.m_vecImpl);
	}
	void CInheritableTypeRegCodeWriter2::CollectDataForGenH(SCollectingGeneratedBodyWritingData& data) const
	{
		data.m_generatedBodyLineNumber = m_generatedBodyLineNumber;
	}
	void CInheritableTypeRegCodeWriter2::WriteStaticInitType(const STypeRegClassWritingContext& context, CCodeLines& lines) const
	{
		ASSERT(false);
//		if (m_baseTaggedType != NULL)
//		{
//			static const char* aaaaaaaaaaaaaaaaa =
//R"(static void StaticInitType()
//{
//	auto type = (Cast)StaticGetType<${Nihao}>();
//	type->InitInheritableTypeMeta(StaticGetType<${Bucuo}>);
//})";
//			CCodeTemplate tpl1;
//			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
//			CLabelToCodeMapping map;
//			MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot->m_resocursorName);
//			MapLabelToText(map, "Bucuo", m_baseTaggedType->m_taggedResoRoot.m_resocursorName);
//			Niflect::TSet<Niflect::CString> setReplacedLabel;
//			tpl1.ReplaceLabels(map, lines, &setReplacedLabel);
//		}
	}
	void CInheritableTypeRegCodeWriter2::WriteInvokeInitType(const STypeRegClassWritingContext& context, CTypeRegTaggedTypeInitWritingData2& data) const
	{
		if (m_baseTaggedType != NULL)
		{
			CCodeTemplate tpl1;
			ReadTemplateFromRawData(tpl1, HardCodedTemplate::InitTypeCode);
			CLabelToCodeMapping map;
			auto& resocursorName = m_bindingTypeIndexedRoot->m_resocursorName;
			MapLabelToText(map, LABEL_0, resocursorName);
			Niflect::CString codeGetType;
			{
				Niflect::CString infoTypeName;
				if (m_resolvedData->m_taggedMapping.GetDerivedInfoTypeName(m_bindingTypeIndexedRoot->m_taggedTypeIndex, infoTypeName))
				{
					codeGetType = ReplaceLabelToText2(HardCodedTemplate::CastGetTypeCode, LABEL_0, LABEL_1, resocursorName, infoTypeName);
				}
				else
				{
					ASSERT(false);//CNiflectType 不支持 InitInheritableTypeMeta, 因此是一种不应出现的错误, 仅留作备用, 未来可移除
					codeGetType = ReplaceLabelToText1(HardCodedTemplate::GetTypeCode, LABEL_0, resocursorName);
				}
			}
			MapLabelToText(map, LABEL_2, codeGetType);
			MapLabelToText(map, LABEL_3, m_baseTaggedType->m_resocursorName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, data.m_lines, &setReplacedLabel);
		}
	}
}
