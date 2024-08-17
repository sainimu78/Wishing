#pragma once
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Util/ConstCharConcat.h"

#define DEVELOPMENT_ROOT_SOURCE_PATH "E:/S3/S3ResourceEditor_another/engine_ref"

namespace NiflectGenDefinition
{
	namespace FileExt
	{
		constexpr const char* Cpp = ".cpp";
		constexpr const char* H = ".h";
		constexpr const char* PrivateH = ".private.h";
		constexpr const char* GenH = ".gen.h";

		static bool IsCpp(const Niflect::CString& text)
		{
			return NiflectUtil::EndsWith(text, Cpp);
		}
		static bool IsH(const Niflect::CString& text)
		{
			return NiflectUtil::EndsWith(text, H);
		}
	}

	namespace CodeTag
	{
		constexpr const char* BindingSetting = "__NiflectGen_BindingSetting";
		constexpr const char* Type = "__NiflectGen_Type";
		constexpr const char* Field = "__NiflectGen_Field";
		constexpr const char* Method = "__NiflectGen_Method";
		constexpr const char* EnumConstant = "__NiflectGen_EnumConstant";

		static bool IsBindingSetting(const Niflect::CString& text)
		{
			return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::BindingSetting);
		}
		static bool IsType(const Niflect::CString& text)
		{
			return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::Type);
		}
		static bool IsField(const Niflect::CString& text)
		{
			return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::Field);
		}
		static bool IsMethod(const Niflect::CString& text)
		{
			return NiflectUtil::StartsWith(text, NiflectGenDefinition::CodeTag::Method);
		}
	}

	namespace Path
	{
		constexpr const char* CLangParserArgs_I[] = {
			CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/S3Engine"),
			//todo: 现代码未合并到引擎, 因此暂使用SampleTest的路径, 合并后可移除
			CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo"),
			//deprecated: 解析头文件要求依赖生成.gen.h, 如果无法避免依赖.h, 则需要生成该.h
			CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/Generated"),
		};

		//用于旁路clang_parseTranslationUnit过程中STL头文件解析, 可大幅减少耗时
		//todo: 旁路代码极简单, 可只在内存中生成
		constexpr const char* BypassingSTL = CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Niflect/Base/BypassCode/NiflectSTL");
	}

	namespace NiflectFramework
	{
		namespace AccessorTypeName
		{
			constexpr const char* Field = "CField";
			constexpr const char* ArrayField = "CArrayField";
			constexpr const char* CompoundField = "CCompoundField";
		}

		namespace InfoTypeName
		{
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
			constexpr const char* CompoundFieldHeader = "Niflect/Field/CompoundField.h";
		}
	}
}