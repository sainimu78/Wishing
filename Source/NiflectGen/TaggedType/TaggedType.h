#pragma once
#include "NiflectGen/Collector/TaggedNode.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"
#include "NiflectGen/Util/CursorMap.h"
#include "NiflectGen/Collector/AccessorBindingMapping.h"

namespace NiflectGen
{
	class CTaggedTypesMapping
	{
	public:
		void Resolve();
		bool InitIndexedNodeForClassDecl(const CXCursor& cursor, const CAccessorBindingMapping2& accessorBindingMapping, CResolvedCursorNode& indexedParent) const;
		TCursorMap<uint32> m_mapCursorToIndex;
		Niflect::TArrayNif<CTaggedType*> m_vecType;
	};

	class CResolvingDependenciesContext
	{
	public:
		CResolvingDependenciesContext(const SResolvedMappings& mappings, CGenLog* log)
			: m_mappings(mappings)
			, m_log(log)
		{

		}
		const SResolvedMappings& m_mappings;
		CGenLog* m_log;
	};

	struct SResolvingDependenciesData
	{
		CResolvedCursorRootsMapping& m_signatureMapping;
	};

	class CTaggedType : public CTaggedNode2
	{
	public:
		CTaggedType()
		{
		}

	public:
		void ResolveForResocursorNode();

	public:
		virtual void Deprecated_ResolveDependcies(const TCursorMap<CTaggedType*>& mapCursorDeclToTaggedType)
		{

		}
		virtual void ResolveDependcies(const CResolvingDependenciesContext& context, SResolvingDependenciesData& data);
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
		virtual CSharedTypeRegCodeWriter2 CreateCodeWriter2() const
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
		Niflect::CString m_resocursorName;
		CResolvedCursorNode m_taggedResoRoot;
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
		void ResolveForAlias(const CAliasChain& aliasChain, const CUntaggedTemplatesMapping& untaggedMapping);

	public:
		static CUntaggedTemplate* CastChecked(inherited* base)
		{
			return dynamic_cast<CUntaggedTemplate*>(base);
		}

	public:
		CUntaggedTemplate* m_originalUntaggedDecl;
	};

	Niflect::CString ResolveSignature(const CResolvedCursorNode& indexedParent, const CResolvingDependenciesContext& ctx, CResolvedCursorRootsMapping& signatureMapping);
}