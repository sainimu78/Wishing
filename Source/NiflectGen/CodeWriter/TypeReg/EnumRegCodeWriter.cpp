#include "NiflectGen/CodeWriter/TypeReg/EnumRegCodeWriter.h"
#include "NiflectGen/util/CursorUtil.h"
#include "NiflectGen/CodeWriter/HardCoded/EnumTemplate.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"

namespace NiflectGen
{
	CEnumRegCodeWriter::CEnumRegCodeWriter(const CXCursor& cursor, const STypeRegClassWritingSetting& writingSetting)
		: inherited(cursor, writingSetting)
	{
	}
	void CEnumRegCodeWriter::WriteDecl(const CWritingContext& context, CTypeRegDeclWrittingData& data) const
	{
	}
	void CEnumRegCodeWriter::WriteImpl(const CWritingContext& context, CTypeRegImplWrittingData& data) const
	{
		data.m_lines.push_back("todo: Enum writer\n");
	}
	void CEnumRegCodeWriter::WriteClass(const CWritingContext& context, CTypeRegClassWrittingData& data) const
	{
		data.m_lines.push_back("todo: Enum writer\n");
	}
	Niflect::CString CEnumRegCodeWriter::WriteTypeRegClassName() const
	{
		return ReplaceLabelToText1(HardCodedTemplate::TypeRegClassScopeName_Enum, LABEL_SHARED_3, m_typeName);
	}
	void CEnumRegCodeWriter::GetInvokationRequirement(CTypeRegInvokationData& data) const
	{
		data.m_requiredInvokationInitType = true;
	}
	Niflect::CString CEnumRegCodeWriter::GetInfoTypeName() const
	{
		return GetCursorInfoTypeName(m_cursor);
	}
}