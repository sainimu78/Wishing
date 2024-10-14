#include "NiflectGen/CodeWriter/TypeReg/MiscTypeRegCodeWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"

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