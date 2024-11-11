#pragma once
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Util/ConcatHardCodedStrings.h"

#define DEVELOPMENT_ROOT_SOURCE_PATH "E:/S3/S3ResourceEditor_another/engine_ref"
#define ROOT_TEST_PATH "F:/Fts/Proj/Test/Interedit/Source/NiflectGen/Test"

namespace NiflectGenDefinition
{
#define FILE_NAME_POSTFIX "_gen"

	namespace FileNamePostfix
	{
		constexpr const char* Gen = FILE_NAME_POSTFIX;
	}
	namespace FileExt
	{
		constexpr const char* Cpp = ".cpp";
		constexpr const char* H = ".h";
		constexpr const char* PrivateH = "_private.h";
		constexpr const char* GenH = CONCAT_HARDCODED_STRINGS_2(FILE_NAME_POSTFIX, ".h");//"_gen.h";

		static bool IsCpp(const Niflect::CString& text)
		{
			return NiflectUtil::EndsWith(text, Cpp);
		}
		static bool IsH(const Niflect::CString& text)
		{
			return NiflectUtil::EndsWith(text, H);
		}
	}

	namespace DirName
	{
		constexpr const char* ModuleReg = "ModuleReg";
		constexpr const char* TypeReg = "TypeReg";
		constexpr const char* GenH = "GenH";
	}

	namespace CodeTag
	{
#ifdef ACCESSOR_SETTING_ABCD
#else
		constexpr const char* BindingSetting = "__NiflectGen_BindingSetting";
#endif
		constexpr const char* GeneratedBody = "__NiflectGen_GeneratedBody";

		constexpr const char* Type = "__NiflectGen_Type";
		constexpr const char* Field = "__NiflectGen_Field";
		constexpr const char* Method = "__NiflectGen_Method";
		constexpr const char* EnumConstant = "__NiflectGen_EnumConstant";

#ifdef ACCESSOR_SETTING_ABCD
		//static bool IsAccessorSettingA(const Niflect::CString& text)
		//{
		//	return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::AccessorSettingA);
		//}
		//static bool IsAccessorSettingB(const Niflect::CString& text)
		//{
		//	return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::AccessorSettingB);
		//}
		//static bool IsAccessorSettingC(const Niflect::CString& text)
		//{
		//	return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::AccessorSettingC);
		//}
		//static bool IsAccessorSettingD(const Niflect::CString& text)
		//{
		//	return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::AccessorSettingD);
		//}
#else
		static bool IsBindingSetting(const Niflect::CString& text)
		{
			return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::BindingSetting);
		}
#endif
		//static bool IsType(const Niflect::CString& text)
		//{
		//	return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::Type);
		//}
		//static bool IsField(const Niflect::CString& text)
		//{
		//	return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::Field);
		//}
		//static bool IsMethod(const Niflect::CString& text)
		//{
		//	return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::Method);
		//}
	}

	namespace CodeStyle
	{
		constexpr const bool AddingSpaceBetweenNestedTemplateRightAngleBrackets = true;
		static void TryFormatNestedTemplate(Niflect::CString& str)
		{
			if (AddingSpaceBetweenNestedTemplateRightAngleBrackets)
			{
				if (str.back() == '>')
					str += ' ';
			}
		}
		static void TemplateAngleBracketL(Niflect::CString& str)
		{
			str += '<';
		}
		static void TemplateAngleBracketR(Niflect::CString& str)
		{
			TryFormatNestedTemplate(str);
			str += '>';
		}
	}

	namespace Path
	{
		constexpr const char* CLangParserArgs_I2[] = {
			CONCAT_HARDCODED_STRINGS_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/S3Engine"),
			//todo: 现代码未合并到引擎, 因此暂使用SampleTest的路径, 合并后可移除
			CONCAT_HARDCODED_STRINGS_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo"),
			//deprecated: 解析头文件要求依赖生成.gen.h, 如果无法避免依赖.h, 则需要生成该.h
			CONCAT_HARDCODED_STRINGS_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/Generated"),
		};

		//用于旁路clang_parseTranslationUnit过程中STL头文件解析, 可大幅减少耗时
		//todo: 旁路代码极简单, 可只在内存中生成
		//constexpr const char* BypassingSTL = CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Niflect/Base/BypassCode/NiflectSTL");
	}

	namespace NiflectFramework
	{
		namespace ScopeName
		{
			constexpr const char* Niflect = "Niflect";
		}

		namespace AccessorTypeName
		{
			constexpr const char* Field = "CAccessor";
			constexpr const char* ArrayField = "CArrayField";
			constexpr const char* CompoundField = "CCompoundAccessor";
		}

		namespace InfoTypeName
		{
			constexpr const char* NiflectType = "CNiflectType";
			constexpr const char* Struct = "CStruct";
			constexpr const char* Class = "CClass";
			constexpr const char* Enum = "CEnum";
		}

		namespace FileName
		{
			constexpr const char* BypassingHeader = "NiflectSTLDeclaration.h";
		}

		namespace FilePath
		{
#ifdef USER_PROVIDED_CCOMPONENTFIELD_CLASS_DEFINITION
			constexpr const char* CompoundFieldHeader = "Niflect/Field/CompoundField.h";
#endif
			constexpr const char* NiflectTypeHeader = "Niflect/NiflectType.h";
			constexpr const char* NiflectTableHeader = "Niflect/NiflectTable.h";
			constexpr const char* NiflectMacroHeader = "Niflect/NiflectMacro.h";
		}

		namespace Setting
		{
			constexpr uint32 ThresholdLinesCountForModuleRegSplitting = 1000;
		}

		namespace BypassSTL
		{
			constexpr const char* HeadersDirName = "BypassSTL";
			constexpr const char* DefaultHeaderFileName = "NiflectSTLDeclaration.h";
		}
	}
}