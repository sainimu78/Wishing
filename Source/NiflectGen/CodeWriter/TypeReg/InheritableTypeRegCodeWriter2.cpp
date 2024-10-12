#include "NiflectGen/CodeWriter/TypeReg/InheritableTypeRegCodeWriter2.h"
#include "NiflectGen/util/CursorUtil.h"
#include "NiflectGen/CodeWriter/HardCoded/InheritableTypeTemplate.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Util/TypeUtil.h"

namespace NiflectGen
{
	CInheritableTypeRegCodeWriter2::CInheritableTypeRegCodeWriter2(const CResolvedCursorNode& bindingTypeIndexedRoot, const Niflect::TArrayNif<CResolvedCursorNode>& vecMemberIndexedRoot, const CTaggedType* baseTaggedType)
		: m_bindingTypeIndexedRoot(bindingTypeIndexedRoot)
		, m_vecMemberIndexedRoot(vecMemberIndexedRoot)
		, m_baseTaggedType(baseTaggedType)
	{

	}
	void CInheritableTypeRegCodeWriter2::WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const
	{
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(BBBBBBBB<${Nihao}>)"
;
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			data.m_fieldLayoutFuncName = ReplaceLabelToText1(aaaaaaaaaaaaaaaaa, "Nihao", m_bindingTypeIndexedRoot.m_resoCursorName);
		}
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(table->RegisterType<${Nihao}>("${Nihao}", &${Bucuo});)"
;
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			CLabelToCodeMapping map;
			MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot.m_resoCursorName);
			MapLabelToText(map, "Bucuo", data.m_fieldLayoutFuncName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, data.m_linesRegisterType, &setReplacedLabel);
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
			CCodeLines linesMembers;
			for (auto& it : m_vecMemberIndexedRoot)
				linesMembers.push_back(it.m_resoCursorName);
			MapLabelToLines(map, "Shima", linesMembers);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, data.m_linesFieldLayoutImpl, &setReplacedLabel);
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
			MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot.m_resoCursorName);
			MapLabelToText(map, "Bucuo", m_baseTaggedType->m_classDeclIndexedRoot.m_resoCursorName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, lines, &setReplacedLabel);
		}
	}
	void CInheritableTypeRegCodeWriter2::WriteTypeRegClass(const STypeRegClassWritingContext& context, CTypeRegClassWritingData2& data) const
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
		MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot.m_resoCursorName);
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
	void CInheritableTypeRegCodeWriter2::WriteTaggedTypeInit(const STypeRegClassWritingContext& context, CTypeRegTaggedTypeInitWritingData2& data) const
	{
		if (m_baseTaggedType != NULL)
		{
			static const char* aaaaaaaaaaaaaaaaa =
R"(auto type = (Cast)StaticGetType<${Nihao}>();
type->InitInheritableTypeMeta(StaticGetType<${Bucuo}>);)";
			CCodeTemplate tpl1;
			tpl1.ReadFromRawData(aaaaaaaaaaaaaaaaa);
			CLabelToCodeMapping map;
			MapLabelToText(map, "Nihao", m_bindingTypeIndexedRoot.m_resoCursorName);
			MapLabelToText(map, "Bucuo", m_baseTaggedType->m_classDeclIndexedRoot.m_resoCursorName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl1.ReplaceLabels(map, data.m_lines, &setReplacedLabel);
		}
	}
}