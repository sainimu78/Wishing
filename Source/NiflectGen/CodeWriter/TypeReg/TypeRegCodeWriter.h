#pragma once
#include "NiflectGen/CodeWriter/CodeWriter.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCode.h"
#include "clang-c/Index.h"
#include "NiflectGen/CodeWriter/CodeRequirement.h"

namespace NiflectGen
{
	class CTypeRegDeclWrittingData
	{
	public:
		CTypeRegDeclWrittingData(CCodeLines& lines)
			: m_lines(lines)
		{

		}

		CCodeLines& m_lines;
	};

	class CTypeRegImplWrittingData
	{
	public:
		CTypeRegImplWrittingData(CCodeLines& lines)
			: m_lines(lines)
		{

		}

		CCodeLines& m_lines;
	};

	class CTypeRegClassWrittingData
	{
	public:
		CTypeRegClassWrittingData(CCodeLines& lines, CNoDupPathCollector& includePathRequirement)
			: m_lines(lines)
			, m_includePathRequirement(includePathRequirement)
		{

		}

		CCodeLines& m_lines;
		CNoDupPathCollector& m_includePathRequirement;
	};

	class CResolvedMapping;

	struct STypeRegClassWritingSetting
	{
		const Niflect::TArrayNif<Niflect::CString>& m_vecHeaderSearchPath;
		const CResolvedMapping& m_mapping;
	};

	class CTypeRegCodeWriter
	{
	public:
		CTypeRegCodeWriter(const CXCursor& cursor, const STypeRegClassWritingSetting& writingSetting);

	public:
		virtual void Init();//预留缓存模板, 获取namespace等
		virtual void WriteDecl(const CWritingContext& context, CTypeRegDeclWrittingData& data) const
		{
		}
		virtual void WriteImpl(const CWritingContext& context, CTypeRegImplWrittingData& data) const
		{
		}
		virtual void WriteClass(const CWritingContext& context, CTypeRegClassWrittingData& data) const = 0;
		void WriteGenHeaderDeclaration(const CWritingContext& context, STypeRegGenHeaderDeclarationWritingData& data) const;
		void WritePrivateHeaderIncludePath(const CWritingContext& context, CNoDupPathCollector& includePathRequirement) const;
		virtual Niflect::CString WriteTypeRegClassName() const = 0;
		virtual void GetInvokationRequirement(CTypeRegInvokationData& data) const = 0;
		virtual Niflect::CString GetInfoTypeName() const = 0;
		const Niflect::TArrayNif<Niflect::CString>& GetNamespaces() const
		{
			return m_vecNamespace;
		}

	protected:
		void CollectIncludePathFromCursor(const CWritingContext& context, const CXCursor& cursor, CNoDupPathCollector& includePathRequirement) const;

	protected:
		const CXCursor& m_cursor;
		Niflect::CString m_typeName;
		Niflect::CString m_typeNameWithScope;
		Niflect::TArrayNif<Niflect::CString> m_vecNamespace;
		const STypeRegClassWritingSetting m_writingSetting;
	};

	using CSharedTypeRegCodeWriter = Niflect::TSharedPtr<CTypeRegCodeWriter>;
}