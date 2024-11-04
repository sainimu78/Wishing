#pragma once
#include "NiflectGen/TaggedType/TaggedType.h"

namespace NiflectGen
{
	class CTaggedInheritableType : public CTaggedType
	{
		typedef CTaggedType inherited;
	public:
		CTaggedInheritableType();

	protected:
		void InitBaseTypeSpecifierCursor(const CXCursor& cursor);
		bool CollectGeneratedBodyTag(const CXCursor& cursor, const CXCursorKind& kind);
		void ErrorIfNoGeneratedBodyTag(const CXCursor& cursor) const;

	public:
		virtual void Deprecated_ResolveDependcies(const TCursorMap<CTaggedType*>& mapCursorDeclToTaggedType) override;
		virtual void ResolveDependcies(const CResolvingDependenciesContext& context, SResolvingDependenciesData& data) override;
		virtual CSharedTypeRegCodeWriter Deprecated_CreateCodeWriter(const STypeRegClassWritingSetting& setting) const override;
		virtual CSharedTypeRegCodeWriter CreateCodeWriter(const STypeRegClassWritingSetting& setting) const override;
		virtual CSharedTypeRegCodeWriter2 CreateCodeWriter2() const override;

	protected:
		virtual void DebugDerivedPrint(FILE* fp) const override;

	private:
		CXCursor m_baseTypeSpecifierCursor;
		CTaggedType* m_baseTaggedType;
		Niflect::TArrayNif<CTaggedInheritableTypeMember*> m_vecMember;
		Niflect::TArrayNif<CResolvedCursorNode> m_vecMemberIndexedRoot;
		uint32 m_generatedBodyLineNumber;
	};
}