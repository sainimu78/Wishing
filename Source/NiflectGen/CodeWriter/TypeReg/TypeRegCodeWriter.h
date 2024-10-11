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
	class CResolvingDependenciesContext;

	struct STypeRegClassWritingSetting
	{
		const Niflect::TArrayNif<Niflect::CString>& m_vecHeaderSearchPath;
		const CResolvedMapping& deprecated_m_mapping;
		const CResolvingDependenciesContext& m_resolvedMappings;
	};

	class CTypeRegCodeWriter
	{
	public:
		CTypeRegCodeWriter(const CXCursor& cursor, const STypeRegClassWritingSetting& writingSetting);

	public:
		virtual void Deprecated_Init() {}
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

	class CTypeRegClassWritingData2
	{
	public:
		CCodeLines m_linesImpl;
	};

	class CTypeRegRegisterAndFieldLayoutWritingData
	{
	public:
		CCodeLines m_linesRegisterType;
		CCodeLines m_linesFieldLayoutDecl;
		CCodeLines m_linesFieldLayoutImpl;
		Niflect::CString m_fieldLayoutFuncName;
		Niflect::TArrayNif<const Niflect::CString*> m_vecHeaderFilePathRef;//只需要引用缓存在IndexedNode中的路径地址, 在生成无重复includes时才需要获取实际字符串
	};

	class CTypeRegTaggedTypeInitWritingData2
	{
	public:
		CCodeLines m_lines;
	};

	class CTypeRegWritingData2
	{
	public:
		CTypeRegRegisterAndFieldLayoutWritingData m_registerTypeAndfieldLayout;
		CTypeRegTaggedTypeInitWritingData2 m_taggedTypeInit;
	};

	struct STypeRegClassWritingContext
	{
		const CCodeLines& m_linesRegisterType;
		const Niflect::CString& m_fieldLayoutFuncName;
		CGenLog* m_log;
	};

	class CTypeRegCodeWriter2
	{
	public:
		virtual void WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const = 0;
		virtual void WriteTypeRegClass(const STypeRegClassWritingContext& context, CTypeRegClassWritingData2& data) const {}
		virtual void WriteTaggedTypeInit(const STypeRegClassWritingContext& context, CTypeRegTaggedTypeInitWritingData2& data) const {}
	};
	using CSharedTypeRegCodeWriter2 = Niflect::TSharedPtr<CTypeRegCodeWriter2>;
}