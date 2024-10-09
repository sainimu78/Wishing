#include "NiflectGen/TaggedType/TaggedType.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "Niflect/Util/DebugUtil.h"

namespace NiflectGen
{
	void CTaggedTypesMapping::InitPatterns()
	{
		for (auto& it : m_vecType)
			it->InitPattern();
	}
	bool CTaggedTypesMapping::InitIndexedNodeForClassDecl(const CXCursor& cursor, CBindingAccessorIndexedNode& indexedParent) const
	{
		auto itFound = m_mapCursorToIndex.find(cursor);
		if (itFound != m_mapCursorToIndex.end())
		{
			ASSERT(!indexedParent.IsValid());
			indexedParent.InitForClassDecl(m_vecType[itFound->second]->m_typeNamePattern, itFound->second);
			return true;
		}
		return false;
	}

	void CTaggedType::InitPattern()
	{
		auto& cursor = this->GetCursor();
		auto signature = GenerateNamespacesAndScopesCode(cursor);
		signature += CXStringToCString(clang_getCursorSpelling(cursor));
		m_typeNamePattern = signature;
	}

	CTaggedInheritableTypeMember::CTaggedInheritableTypeMember()
		: m_accessSpecifier(CX_CXXPrivate)
	{

	}
	void CTaggedInheritableTypeMember::InitMember(CX_CXXAccessSpecifier accessSpecifier)
	{
		m_accessSpecifier = accessSpecifier;
	}
	bool CTaggedInheritableTypeMember::CollectSibling(const CXCursor& cursor, const STaggedNodeCollectingContext& context)
	{
		m_vecDetailCursor.push_back(cursor);
		return false;
	}
	void CTaggedInheritableTypeMember::DebugDerivedPrint(FILE* fp) const
	{
		const char* memberTypeStr = NULL;
		switch (clang_getCursorKind(this->GetCursor()))
		{
		case CXCursor_FieldDecl: memberTypeStr = "A field"; break;
		case CXCursor_CXXMethod: memberTypeStr = "A method"; break;
		}

		const char* accessStr = NULL;
		switch (m_accessSpecifier) {
		case CX_CXXInvalidAccessSpecifier:
			ASSERT(false);
			accessStr = "invalid"; break;
		case CX_CXXPublic:
			accessStr = "public"; break;
		case CX_CXXProtected:
			accessStr = "protected"; break;
		case CX_CXXPrivate:
			accessStr = "private"; break;
		}
		printf(", %s, %s", memberTypeStr, accessStr);
	}

	CUntaggedTemplate::CUntaggedTemplate()
	{
	}
	bool CUntaggedTemplate::CollectSibling(const CXCursor& cursor, const STaggedNodeCollectingContext& context)
	{
		bool addedTaggedChild = false;
		auto kind = clang_getCursorKind(cursor);
		bool ok = false;
		if (kind == CXCursor_FieldDecl)
			ok = true;
		if (ok)
		{
			auto taggedChild = Niflect::MakeShared<CTaggedInheritableTypeMember>();
			this->AddChildAndInitDefault(taggedChild, cursor, g_invalidCursor);
			addedTaggedChild = true;
		}
		return addedTaggedChild;
	}
}