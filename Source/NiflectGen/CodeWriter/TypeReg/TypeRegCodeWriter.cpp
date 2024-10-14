#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"
#include "NiflectGen/Util/CursorUtil.h"
//#include "NiflectGen/CodeWriter/HardCoded/TypeRegGenHeaderDeclTemplate.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/HardCoded/TypeRegInitialRegTemplate.h"
#include "NiflectGen/Resolver/ResolvedData.h"

namespace NiflectGen
{
	CTypeRegCodeWriter::CTypeRegCodeWriter(const CXCursor& cursor, const STypeRegClassWritingSetting& writingSetting)
		: m_cursor(cursor)
		, m_writingSetting(writingSetting)
	{
		//m_typeName = CXStringToCString(clang_getCursorSpelling(m_cursor));
		//m_typeNameWithScope = CXStringToCString(clang_getTypeSpelling(clang_getCursorType(m_cursor)));
		//Niflect::TArrayNif<Niflect::CString> vecDeclScope;
		//FindNamespaceAndScopeNameRecursOld(m_cursor, m_vecNamespace, vecDeclScope);
	}
	void CTypeRegCodeWriter::WriteGenHeaderDeclaration(const CWritingContext& context, STypeRegGenHeaderDeclarationWritingData& data) const
	{
		//data.m_linesTypeDeclaration.push_back(ReplaceLabelToText1(HardCodedTemplate::TypeRegGenHeader_TypeDecl, LABEL_0, m_typeName));

		//{
		//	CCodeTemplate tpl;
		//	tpl.ReadFromRawData(HardCodedTemplate::TypeRegGenHeader_StaticGetTypeSpecialization);
		//	CLabelToCodeMapping map;
		//	MapLabelToText(map, LABEL_1, m_typeNameWithScope);
		//	tpl.ReplaceLabels(map, data.m_linesStaticGetTypeSpecialization);
		//}

		//{
		//	CCodeTemplate tpl;
		//	tpl.ReadFromRawData(HardCodedTemplate::TypeRegGenHeader_ExposedPrivateMacro);
		//	CLabelToCodeMapping map;
		//	MapLabelToText(map, LABEL_0, "reserved_decl_without_namespace");
		//	MapLabelToText(map, LABEL_2, "reserved_file_id");
		//	MapLabelToText(map, LABEL_3, "reserved_line_number");
		//	tpl.ReplaceLabels(map, data.m_linesExposedPrivateMacro);
		//}
	}
	void CTypeRegCodeWriter::WritePrivateHeaderIncludePath(const CWritingContext& context, CNoDupPathCollector& includePathRequirement) const
	{
		this->CollectIncludePathFromCursor(context, m_cursor, includePathRequirement);
	}
	void CTypeRegCodeWriter::CollectIncludePathFromCursor(const CWritingContext& context, const CXCursor& cursor, CNoDupPathCollector& includePathRequirement) const
	{
		auto filePath = GetCursorFilePath(cursor);

		if (!NiflectUtil::EndsWith(filePath, NiflectGenDefinition::NiflectFramework::FileName::BypassingHeader))
		{
			includePathRequirement.Add(CIncludesHelper::ConvertToIncludePath(filePath, m_writingSetting.m_vecHeaderSearchPath));
		}
		else
		{
			//todo: 专门处理STL的类型:
			//1. 不在NiflectSTLDeclaration.h集中声明, 分散到同名旁路头文件如std::string移到string文件中
			//2. NiflectSTLDeclaration.h扩展用法, 用于表示不能被Binding的STL类型
			//3. 对获取到的路径检查是否为旁路代码路径, 是则转换为STL风格的路径
			//4. 如果路径为NiflectSTLDeclaration.h, 则报错, 提示不能Binding
			auto type = clang_getCursorType(cursor);
			GenLogError(context.m_log, NiflectUtil::FormatString("Does not support binding type %s", CXStringToCString(clang_getTypeSpelling(type)).c_str()));
		}
	}

	CTypeRegCodeWriter2::CTypeRegCodeWriter2()
		: m_resolvedData(NULL)
		, m_bindingTypeIndexedRoot(NULL)
	{

	}
	void CTypeRegCodeWriter2::Init(const CResolvedData* resolvedData, const CResolvedCursorNode* bindingTypeIndexedRoot)
	{
		m_bindingTypeIndexedRoot = bindingTypeIndexedRoot;
		m_resolvedData = resolvedData;
	}
	void CTypeRegCodeWriter2::WriteInvokeRegisterType(const CWritingContext& context, STypeRegInvokeRegisterTypeWritingData& data) const
	{
		{
			auto& hct = HardCodedTemplate::CreateFieldLayuotOfTypeFuncName;
			auto cursorName = m_bindingTypeIndexedRoot->m_resocursorName;
			NiflectGenDefinition::CodeStyle::TryFormatNestedTemplate(cursorName);
			data.m_createFieldLayoutOfTypeFuncName = ReplaceLabelToText1(hct, LABEL_0, cursorName);
		}
		{
			auto& hct = HardCodedTemplate::InvokeRegisterType;
			CCodeTemplate tpl0;
			tpl0.ReadFromRawData(hct);
			CLabelToCodeMapping map;
			MapLabelToText(map, LABEL_0, m_bindingTypeIndexedRoot->m_resocursorName);
			Niflect::CString infoTypeName = NiflectGenDefinition::NiflectFramework::InfoTypeName::NiflectType;
			{
				if (m_bindingTypeIndexedRoot->m_taggedTypeIndex != INDEX_NONE)
				{
					ASSERT(m_bindingTypeIndexedRoot->m_accessorBindingIndex == INDEX_NONE);
					auto& tagged = m_resolvedData->m_taggedMapping.m_vecType[m_bindingTypeIndexedRoot->m_taggedTypeIndex];
					auto& cursor = tagged->GetCursor();
					auto kind = clang_getCursorKind(cursor);
					switch (kind)
					{
					case CXCursor_ClassDecl: infoTypeName = NiflectGenDefinition::NiflectFramework::InfoTypeName::Class; break;
					case CXCursor_StructDecl: infoTypeName = NiflectGenDefinition::NiflectFramework::InfoTypeName::Struct; break;
					case CXCursor_EnumDecl: infoTypeName = NiflectGenDefinition::NiflectFramework::InfoTypeName::Enum; break;
					default:
						break;
					}
				}
			}
			MapLabelToText(map, LABEL_1, infoTypeName);
			MapLabelToText(map, LABEL_2, data.m_createFieldLayoutOfTypeFuncName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl0.ReplaceLabels(map, data.m_linesInvokeRegisterType, &setReplacedLabel);
			ASSERT(setReplacedLabel.size() == map.size());
		}
	}
	void CTypeRegCodeWriter2::WriteCreateFieldLayoutOfType(const STypeRegCreateFieldLayoutOfTypeWritingContext& context, STypeRegCreateFieldLayoutOfTypeWritingData& data) const
	{
		{
			auto& hct = HardCodedTemplate::CreateFieldLayoutOfTypeDecl;
			CCodeTemplate tpl0;
			tpl0.ReadFromRawData(hct);
			CLabelToCodeMapping map;
			MapLabelToText(map, LABEL_2, context.m_createFieldLayoutOfTypeFuncName);
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl0.ReplaceLabels(map, data.m_linesCreateFieldLayoutOfTypeDecl, &setReplacedLabel);
			ASSERT(setReplacedLabel.size() == map.size());
		}
		{
			auto& hct = HardCodedTemplate::CreateFieldLayoutOfTypeImpl;
			CCodeTemplate tpl0;
			tpl0.ReadFromRawData(hct);
			CLabelToCodeMapping map;
			MapLabelToText(map, LABEL_2, context.m_createFieldLayoutOfTypeFuncName);
			CCodeLines linesBody;
			{
				Niflect::CString accessorResoCursorName;
				if (m_bindingTypeIndexedRoot->m_accessorBindingIndex != INDEX_NONE)
				{
					auto& setting = m_resolvedData->m_accessorBindingMapping->m_vecAccessorBindingSetting[m_bindingTypeIndexedRoot->m_accessorBindingIndex];
					accessorResoCursorName = setting.m_accessorTypeCursorName;
					
					if (IsCursorTemplateDecl(setting.GetAccessorTypeDecl().m_cursorDecl))//注, 特化的 Kind 为 ClassDecl
					{
						auto& arg = m_bindingTypeIndexedRoot->m_resocursorName;

						NiflectGenDefinition::CodeStyle::TemplateAngleBracketL(accessorResoCursorName);
						accessorResoCursorName += arg;
						NiflectGenDefinition::CodeStyle::TemplateAngleBracketR(accessorResoCursorName);
					}

					//if (clang_getCursorKind(setting.GetAccessorTypeDecl().m_cursorDecl) != CXCursor_ClassDecl)
					//{
					//	auto argsCount = clang_Type_getNumTemplateArguments(setting.GetAccessorTypeDecl().m_CXType);
					//	if (argsCount > 0)
					//	{
					//		auto& arg = m_bindingTypeIndexedRoot->m_resocursorName;

					//		NiflectGenDefinition::CodeStyle::TemplateAngleBracketL(accessorResoCursorName);
					//		accessorResoCursorName += arg;
					//		NiflectGenDefinition::CodeStyle::TemplateAngleBracketR(accessorResoCursorName);
					//	}
					//}
				}
				else
				{
					accessorResoCursorName = "?";
				}
				linesBody.push_back(accessorResoCursorName);
				MapLabelToLines(map, LABEL_3, linesBody);
			}
			Niflect::TSet<Niflect::CString> setReplacedLabel;
			tpl0.ReplaceLabels(map, data.m_linesCreateFieldLayoutOfTypeImpl, &setReplacedLabel);
			ASSERT(setReplacedLabel.size() == map.size());
		}


		DebugPrintCodeLines(data.m_linesCreateFieldLayoutOfTypeImpl);
	}
}