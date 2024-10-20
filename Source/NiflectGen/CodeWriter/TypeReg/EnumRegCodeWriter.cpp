#include "NiflectGen/CodeWriter/TypeReg/EnumRegCodeWriter.h"
#include "NiflectGen/util/CursorUtil.h"
#include "NiflectGen/CodeWriter/HardCoded/EnumTemplate.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"

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

//	void CEnumRegCodeWriter2::WriteForFieldLayout(const STypeRegCreateFieldLayoutOfTypeWritingContext& context, STypeRegCreateFieldLayoutOfTypeWritingData& data) const
//	{
//		//仅留作测试不应生成无关文件的代码, 可移除
//		data.m_linesCreateFieldLayoutOfTypeImpl.push_back(NiflectUtil::FormatString("Reserved WriteForFieldLayout for enum: %s", m_bindingTypeIndexedRoot->m_resocursorName.c_str()));
//#ifdef DEBUG_FOR_TYPE_REG
//		DebugPrintCodeLines(data.m_linesCreateFieldLayoutOfTypeImpl);
//#endif
//	}
	void CEnumRegCodeWriter2::CollectDependencyHeaderFilePaths(CDependencyHeaderFilePathRefs& dependencyHeaderFilePathRefs) const
	{
	}
	void CEnumRegCodeWriter2::WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const
	{
#ifdef TODO_ENUM_CODE_GEN_PIPELINE
		asdf
#else
		data.m_linesInvokeRegisterType.push_back(NiflectUtil::FormatString("Reserved RegisterType for enum: %s", m_bindingTypeIndexedRoot->m_resocursorName.c_str()));
		data.m_linesCreateFieldLayoutOfTypeDecl.push_back(NiflectUtil::FormatString("Reserved FieldLayoutDecl for enum: %s", m_bindingTypeIndexedRoot->m_resocursorName.c_str()));
		data.m_linesCreateFieldLayoutOfTypeImpl.push_back(NiflectUtil::FormatString("Reserved FieldLayoutImpl for enum: %s", m_bindingTypeIndexedRoot->m_resocursorName.c_str()));
#endif
	}
	void CEnumRegCodeWriter2::Deprecated_WriteTypeRegClass(const STypeRegClassWritingContext& context, CTypeRegClassWritingData2& data) const
	{
#ifdef TODO_ENUM_CODE_GEN_PIPELINE
		asdf
#else
		data.m_linesImpl.push_back(NiflectUtil::FormatString("Reserved RegClass for enum: %s", m_bindingTypeIndexedRoot->m_resocursorName.c_str()));
#endif
	}
	void CEnumRegCodeWriter2::WriteInvokeInitType(const STypeRegClassWritingContext& context, CTypeRegTaggedTypeInitWritingData2& data) const
	{
#ifdef TODO_ENUM_CODE_GEN_PIPELINE
		asdf
#else
		data.m_lines.push_back(NiflectUtil::FormatString("Reserved InvokeInitType for enum: %s", m_bindingTypeIndexedRoot->m_resocursorName.c_str()));
#endif
	}
}