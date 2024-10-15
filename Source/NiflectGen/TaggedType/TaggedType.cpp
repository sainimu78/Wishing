#include "NiflectGen/TaggedType/TaggedType.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "Niflect/Util/DebugUtil.h"

namespace NiflectGen
{
	static Niflect::CString ResolveSignatureRecurs(const CResolvedCursorNode& indexedParent, const CResolvedCursorNode& childrenOwnerOld, const CResolvingDependenciesContext& ctx, CResolvedCursorRootsMapping& signatureMapping)
	{
		auto ret = signatureMapping.m_mapKeyToIndex.insert({ indexedParent.m_key, static_cast<uint32>(signatureMapping.m_vecItem.size()) });
		if (ret.second)
		{
			auto& childrenOwner = indexedParent;
			if (indexedParent.m_accessorBindingIndex != INDEX_NONE)
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
			else if (indexedParent.m_taggedTypeIndex != INDEX_NONE)
			{
				//类或结构体定义不继续递归, 计划在生成阶段遍历member
				ASSERT(childrenOwner.m_vecChild.size() == 0);
				ASSERT(indexedParent.m_elem == NULL);
			}
			else
			{
				ASSERT(false);
			}
			signatureMapping.m_vecItem.push_back(CResolvedCursorRoots(Niflect::CString(), indexedParent));
		}
		else
		{
		}

		return Niflect::CString();
	}

	Niflect::CString ResolveSignature(const CResolvedCursorNode& indexedParent, const CResolvingDependenciesContext& ctx, CResolvedCursorRootsMapping& signatureMapping)
	{
		return ResolveSignatureRecurs(indexedParent, indexedParent, ctx, signatureMapping);
	}

	void CTaggedType::ResolveDependcies(const CResolvingDependenciesContext& context, SResolvingDependenciesData& data)
	{
		auto& taggedMapping = context.m_mappings.m_tagged;
		auto& cursor = this->GetCursor();
		ASSERT(!m_taggedResoRoot.IsValid());
#ifdef TODO_SIMPLIFY_TAGGED_TYPE_INDEXED_ROOT_INITIALIZATION
		实际上在插入到 taggedMapping 时, 就已经能正确获取 IndexedRoot 需要的信息, 因此可考虑简化流程
#else
#endif
		if (!taggedMapping.InitIndexedNodeForClassDecl(cursor, context.m_mappings.m_accessorBinding, m_taggedResoRoot))
		{
			ASSERT(false);
		}
		ResolveSignature(m_taggedResoRoot, context, data.m_signatureMapping);
	}

	void CTaggedTypesMapping::Resolve()
	{
		for (auto& it : m_vecType)
			it->ResolveForResocursorNode();
	}
	bool CTaggedTypesMapping::InitIndexedNodeForClassDecl(const CXCursor& cursor, const CAccessorBindingMapping2& accessorBindingMapping, CResolvedCursorNode& indexedParent) const
	{
		auto itFound = m_mapCursorToIndex.find(cursor);
		if (itFound != m_mapCursorToIndex.end())
		{
			ASSERT(!indexedParent.IsValid());
			auto headerFilePath = GetCursorFilePath(cursor);
			ASSERT(!headerFilePath.empty());
			uint32 taggedTypeIdx = INDEX_NONE;
			auto itFound2 = accessorBindingMapping.m_mapSpecializedCursorToIndex.find(cursor);
			if (itFound2 != accessorBindingMapping.m_mapSpecializedCursorToIndex.end())
				taggedTypeIdx = itFound2->second;
			indexedParent.InitForClassDecl(m_vecType[itFound->second]->m_resocursorName, itFound->second, taggedTypeIdx, headerFilePath);
			return true;
		}
		return false;
	}

	void CTaggedType::ResolveForResocursorNode()
	{
		auto& cursor = this->GetCursor();
		auto resocursorName = GenerateNamespacesAndScopesCode(cursor);
		resocursorName += CXStringToCString(clang_getCursorSpelling(cursor));
		m_resocursorName = resocursorName;
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
		: m_originalUntaggedDecl(NULL)
#ifdef BINDING_TYPE_DUPLICATION_VERIFICATION
		, m_argsCount(0)
#else
#endif
	{
	}
	bool CUntaggedTemplate::CollectSibling(const CXCursor& cursor, const STaggedNodeCollectingContext& context)
	{
		bool addedTaggedChild = false;
		auto kind = clang_getCursorKind(cursor);
		bool ok = false;
		if (kind == CXCursor_FieldDecl)
			ok = true;
#ifdef BINDING_TYPE_DUPLICATION_VERIFICATION
		else if (kind == CXCursor_TemplateTypeParameter)
			m_argsCount++;
#else
#endif
		if (ok)
		{
			auto taggedChild = Niflect::MakeShared<CTaggedInheritableTypeMember>();
			this->AddChildAndInitDefault(taggedChild, cursor, g_invalidCursor);
			addedTaggedChild = true;
		}
		return addedTaggedChild;
	}
	void CUntaggedTemplate::InitForAlias(const CAliasChain& aliasChain, const CUntaggedTemplatesMapping& untaggedMapping)
	{
		CXCursor originalCursor;
		//auto a = CXStringToCString(clang_getCursorSpelling(this->GetCursor()));
		//if (a == "_Apply")
		//	printf("");
		//auto dddddddd = aliasChain.FindOriginalDeclOld(this->GetCursor());
		if (aliasChain.FindOriginalDecl(this->GetCursor(), originalCursor))
		{
			auto itFound = untaggedMapping.m_mapCursorToIndex.find(originalCursor);
			//ASSERT(itFound != untaggedMapping.m_mapCursorToIndex.end());
			if (itFound != untaggedMapping.m_mapCursorToIndex.end())
				m_originalUntaggedDecl = untaggedMapping.m_vecType[itFound->second];
		}
	}
}