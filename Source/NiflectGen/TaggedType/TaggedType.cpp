#include "NiflectGen/TaggedType/TaggedType.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "Niflect/Util/DebugUtil.h"

namespace NiflectGen
{
	static Niflect::CString ResolveSignatureRecurs(const CBindingAccessorIndexedNode& indexedParent, const CBindingAccessorIndexedNode& childrenOwnerOld, const CResolvingDependenciesContext& ctx, CSignatureCodeMapping& signatureMapping)
	{
		auto ret = signatureMapping.m_mapSignatureToIndex.insert({ indexedParent.m_key, static_cast<uint32>(signatureMapping.m_vecItem.size()) });
		if (ret.second)
		{
			auto& childrenOwner = indexedParent;
			if (indexedParent.m_settingIdx != INDEX_NONE)
			{
				//for (uint32 idx = 0; idx < childrenOwner.m_vecChild.size(); ++idx)
				//{
				//	auto& it = childrenOwner.m_vecChild[idx];
				//	MakeSignatureForFieldRecurs(it, it, ctx, signatureMapping);
				//}
				if (auto elem = indexedParent.m_elem.Get())
				{
					ASSERT(childrenOwner.m_vecChild.size() == 0);
					ResolveSignatureRecurs(*elem, *elem, ctx, signatureMapping);
				}
				else
				{
					for (auto& it : childrenOwner.m_vecChild)
						ResolveSignatureRecurs(it, it, ctx, signatureMapping);
				}
			}
			else if (indexedParent.m_taggedIdx != INDEX_NONE)
			{
				//类或结构体定义不继续递归, 计划在生成阶段遍历member
				ASSERT(childrenOwner.m_vecChild.size() == 0);
				ASSERT(indexedParent.m_elem == NULL);
			}
			else
			{
				ASSERT(false);
			}
			signatureMapping.m_vecItem.push_back(CSignatureCode(Niflect::CString(), indexedParent));
		}
		else
		{
		}

		return Niflect::CString();
	}

	Niflect::CString ResolveSignature(const CBindingAccessorIndexedNode& indexedParent, const CResolvingDependenciesContext& ctx, CSignatureCodeMapping& signatureMapping)
	{
		return ResolveSignatureRecurs(indexedParent, indexedParent, ctx, signatureMapping);
	}

	void CTaggedType::ResolveDependcies(const CResolvingDependenciesContext& context, SResolvingDependenciesData& data)
	{
		auto& taggedMapping = context.m_mappings.m_tagged;
		auto& cursor = this->GetCursor();
		ASSERT(!m_classDeclIndexedRoot.IsValid());
#ifdef TODO_SIMPLIFY_TAGGED_TYPE_INDEXED_ROOT_INITIALIZATION
		实际上在插入到 taggedMapping 时, 就已经能正确获取 IndexedRoot 需要的信息, 因此可考虑简化流程
#else
#endif
		if (!taggedMapping.InitIndexedNodeForClassDecl(cursor, m_classDeclIndexedRoot))
		{
			ASSERT(false);
		}
		ResolveSignature(m_classDeclIndexedRoot, context, data.m_signatureMapping);
	}

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
			auto headerFilePath = GetCursorFilePath(cursor);
			ASSERT(!headerFilePath.empty());
			indexedParent.InitForClassDecl(m_vecType[itFound->second]->m_typeNamePattern, itFound->second, headerFilePath);
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