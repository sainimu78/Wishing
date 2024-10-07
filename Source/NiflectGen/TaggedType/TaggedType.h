#pragma once
#include "NiflectGen/Collector/TaggedNode.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"
#include "NiflectGen/Util/CursorMap.h"
#include "NiflectGen/Collector/AccessorBindingMapping.h"

namespace NiflectGen
{
	class CTaggedType;

	class CResolvedTaggedTypesMapping
	{
	public:
		bool FindForClassDecl(const CXCursor& cursor, CBindingAccessorIndexedNode& indexedParent) const
		{
			auto itFound = m_mapCursorToIndex.find(cursor);
			if (itFound != m_mapCursorToIndex.end())
			{
				ASSERT(!indexedParent.IsValid());
				indexedParent.InitForClassDecl(itFound->second);
				return true;
			}
			return false;
		}
		TCursorMap<uint32> m_mapCursorToIndex;
		Niflect::TArrayNif<CTaggedType*> m_vecType;
	};

	struct SResolvingDependenciesContext
	{
		const CAccessorBindingMapping2& m_bindingAccessorMapping;
		const CResolvedTaggedTypesMapping& m_resolvedTaggedTypeMapping;
	};

	class CSignatureCode
	{
	public:
		CSignatureCode()
		{
		}
		CSignatureCode(const Niflect::CString& signatureStr)
			: m_signatureStr(signatureStr)
		{
		}
		Niflect::CString m_signatureStr;
	};

	class CSignatureCodeMapping
	{
	public:
		Niflect::TArrayNif<CSignatureCode> m_vecCode;
		Niflect::TMap<Niflect::CString, uint32> m_mapSignatureToIndex;
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