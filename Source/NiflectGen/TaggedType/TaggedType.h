#pragma once
#include "NiflectGen/Collector/TaggedNode.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"
#include "NiflectGen/Util/CursorMap.h"
#include "NiflectGen/Collector/AccessorBindingMapping.h"

namespace NiflectGen
{
	struct SResolvingDependenciesContext
	{
		const CAccessorBindingMapping2& m_accessorBindingMapping;
		const CTaggedTypesMapping& m_taggedMapping;
		const CUntaggedTemplateTypesMapping& m_untaggedTemplateMapping;
	};

	struct SResolvingDependenciesData
	{
		CSignatureCodeMapping& m_signatureMapping;
	};

	class CTaggedType : public CTaggedNode2
	{
	public:
		CTaggedType()
		{
		}

	public:
		void InitPattern();

	public:
		virtual void Deprecated_ResolveDependcies(const TCursorMap<CTaggedType*>& mapCursorDeclToTaggedType)
		{

		}
		virtual void ResolveDependcies(const SResolvingDependenciesContext& context, SResolvingDependenciesData& data)
		{

		}
		virtual CSharedTypeRegCodeWriter Deprecated_CreateCodeWriter(const STypeRegClassWritingSetting& setting) const
		{
			ASSERT(false);
			return NULL;
		}
		virtual CSharedTypeRegCodeWriter CreateCodeWriter(const STypeRegClassWritingSetting& setting) const
		{
			ASSERT(false);
			return NULL;
		}

	public:
		static CTaggedType* CastChecked(CTaggedNode2* base)
		{
			return dynamic_cast<CTaggedType*>(base);
		}

	public:
		Niflect::CString m_typeNamePattern;
	};

	class CTaggedInheritableTypeMember : public CTaggedNode2
	{
		typedef CTaggedNode2 inherited;
	public:
		CTaggedInheritableTypeMember();
		void InitMember(CX_CXXAccessSpecifier accessSpecifier);

	public:
		virtual bool CollectSibling(const CXCursor& cursor, const STaggedNodeCollectingContext& context) override;

	protected:
		virtual void DebugDerivedPrint(FILE* fp) const override;

	public:
		const Niflect::TArrayNif<CXCursor>& GetDetailCursors() const
		{
			return m_vecDetailCursor;
		}

	public:
		static CTaggedInheritableTypeMember* Cast(inherited* base)
		{
			ASSERT(dynamic_cast<CTaggedInheritableTypeMember*>(base) != NULL);
			return static_cast<CTaggedInheritableTypeMember*>(base);
		}
		static CTaggedInheritableTypeMember* CastChecked(inherited* base)
		{
			return dynamic_cast<CTaggedInheritableTypeMember*>(base);
		}

	public:
		CX_CXXAccessSpecifier m_accessSpecifier;
		Niflect::TArrayNif<CXCursor> m_vecDetailCursor;
	};

	//todo: 计划改名为 CUntaggedType
	class CUntaggedTemplate : public CTaggedNode2
	{
		typedef CTaggedNode2 inherited;
	public:
		CUntaggedTemplate();

	public:
		virtual bool CollectSibling(const CXCursor& cursor, const STaggedNodeCollectingContext& context) override;

	public:
		static CUntaggedTemplate* CastChecked(inherited* base)
		{
			return dynamic_cast<CUntaggedTemplate*>(base);
		}
	};
}