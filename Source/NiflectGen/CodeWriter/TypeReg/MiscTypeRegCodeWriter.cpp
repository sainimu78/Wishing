#include "NiflectGen/CodeWriter/TypeReg/MiscTypeRegCodeWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Resolver/ResolvedData.h"

namespace NiflectGen
{
	static void WriteDDDDDDDD(const CResolvedCursorNode& indexedParent, uint32 lv, const char* pszLv, CCodeLines& lines)
	{
		lines.push_back(indexedParent.m_resocursorName);
	}
	static void WriteNexts(const CResolvedCursorNode& indexedParent, CCodeLines& lines)
	{
		uint32 lv = 0;
		const char* pszLv = "-";
		//WriteDDDDDDDD(indexedParent, lv, pszLv, lines);

		lv++;
		auto& childrenOwner = indexedParent;
		if (auto elem = indexedParent.m_elem.Get())
		{
			ASSERT(childrenOwner.m_vecChild.size() == 0);
			WriteDDDDDDDD(*elem, lv, "+", lines);
		}
		else
		{
			for (auto& it : childrenOwner.m_vecChild)
				WriteDDDDDDDD(it, lv, pszLv, lines);
		}
	}
	void CMiscTypeRegCodeWriter::WriteResocursorNodeBodyCode(CCodeLines& linesResoBodyCode) const
	{
		//linesResoBodyCode.push_back(NiflectUtil::FormatString("My Name: %s", m_bindingTypeIndexedRoot->m_resocursorName.c_str()));
		ASSERT(m_bindingTypeIndexedRoot->m_accessorBindingIndex);
		if (m_bindingTypeIndexedRoot->m_untaggedTemplateIndex != INDEX_NONE)
		{
			linesResoBodyCode.push_back("---------------");
			if (auto elemResocursorNode = m_bindingTypeIndexedRoot->m_elem.Get())
			{
				auto d = NiflectUtil::FormatString("Element -> %s", elemResocursorNode->m_resocursorName.c_str());
				linesResoBodyCode.push_back(d);
			}
			else
			{
				auto ut = m_resolvedData->m_untaggedTemplateMapping.m_vecType[m_bindingTypeIndexedRoot->m_untaggedTemplateIndex];
				if (ut->m_originalUntaggedDecl != NULL)
					ut = ut->m_originalUntaggedDecl;
				ASSERT(ut->DebugGetChildren().size() > 0);//需要通过aliasChain查找原始定义, 以获取结构
				ASSERT(m_bindingTypeIndexedRoot->m_vecChild.size() == ut->GetChildrenCount());
				for (uint32 idx = 0; idx < ut->DebugGetChildren().size(); ++idx)
				{
					auto& it = ut->DebugGetChildren()[idx];
					auto& a = m_bindingTypeIndexedRoot->m_vecChild[idx].m_resocursorName;
					auto b = CXStringToCString(clang_getCursorSpelling(it->GetCursor()));
					auto d = NiflectUtil::FormatString("%s %s;", a.c_str(), b.c_str());
					linesResoBodyCode.push_back(d);
				}
			}
		}
	}
	void CMiscTypeRegCodeWriter::WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const
	{
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(AAAAAAA<${Nihao}>)"
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
			data.m_linesFieldLayoutDecl.push_back(funcSignature);
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
			CCodeLines linesNexts;
			WriteNexts(*m_bindingTypeIndexedRoot, linesNexts);
			MapLabelToLines(map, "Shima", linesNexts);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, data.m_linesFieldLayoutImpl, &setReplacedLabel);
		}
	}
}