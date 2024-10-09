#include "NiflectGen/TaggedType/TaggedInheritableType.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "NiflectGen/CodeWriter/TypeReg/InheritableTypeRegCodeWriter.h"
#include "Niflect/Util/TypeUtil.h"
#include "Niflect/Util/DebugUtil.h"

namespace NiflectGen
{
	CTaggedInheritableType::CTaggedInheritableType()
		: m_baseTypeSpecifierCursor(g_invalidCursor)
		, m_baseTaggedType(NULL)
	{
	}
	void CTaggedInheritableType::InitBaseTypeSpecifierCursor(const CXCursor& cursor)
	{
		ASSERT(clang_Cursor_isNull(m_baseTypeSpecifierCursor));
		m_baseTypeSpecifierCursor = cursor;
	}
	void CTaggedInheritableType::Deprecated_ResolveDependcies(const TCursorMap<CTaggedType*>& mapCursorDeclToTaggedType)
	{
		ASSERT(m_baseTaggedType == NULL);
		auto baseTypeCursorDecl = clang_getTypeDeclaration(clang_getCursorType(m_baseTypeSpecifierCursor));
		auto itFound = mapCursorDeclToTaggedType.find(baseTypeCursorDecl);
		if (itFound != mapCursorDeclToTaggedType.end())
			m_baseTaggedType = itFound->second;
	}
#ifdef EMBEDDING_ELEMENT_BINDING_TYPE_INDEXED_NODE
	static void DebugPrintIndexedNodeRecurs(const CBindingAccessorIndexedNode& indexedParent, const CBindingAccessorIndexedNode& childrenOwner, const CAccessorBindingMapping2& mapping, uint32 lv)
	{
		auto strLv = NiflectUtil::DebugIndentToString(lv);
		auto& cxType = mapping.m_vecAccessorBindingSetting[indexedParent.m_settingIdx].GetAccessorTypeDecl().m_CXType;
		auto a = CXStringToCString(clang_getTypeSpelling(cxType));
		printf("%s%s\n", strLv.c_str(), a.c_str());

		lv++;
		for (auto& it : childrenOwner.m_vecChild)
			DebugPrintIndexedNodeRecurs(it, it, mapping, lv);

		if (auto elem = indexedParent.m_elem.Get())
		{
			lv--;
			printf("---------------\n");
			DebugPrintIndexedNodeRecurs(*elem, indexedParent, mapping, lv);
		}
	}
#else
	static void DebugPrintIndexedNodeRecurs(const CBindingAccessorIndexedNode& indexedParent, const CAccessorBindingMapping2& mapping, uint32 lv)
	{
		auto strLv = NiflectUtil::DebugIndentToString(lv);
		auto& cxType = mapping.m_vecAccessorBindingSetting[indexedParent.m_settingIdx].GetAccessorTypeDecl().m_CXType;
		auto a = CXStringToCString(clang_getTypeSpelling(cxType));
		printf("%s%s\n", strLv.c_str(), a.c_str());

		lv++;
		for (auto& it : indexedParent.m_vecChild)
			DebugPrintIndexedNodeRecurs(it, mapping, lv);
	}
	static Niflect::CString GenerateSignatureFromIndexedNodeRecurs(const CBindingAccessorIndexedNode& indexedParent, const CAccessorBindingMapping2& mapping)
	{
		Niflect::CString strArgs;
		auto& subcursor = mapping.m_vecAccessorBindingSetting[indexedParent.m_settingIdx].GetBindingTypeDecl();

		if (indexedParent.IsBindingTypeTemplate())
			strArgs += '<';
		for (uint32 idx = 0; idx < indexedParent.m_vecChild.size(); ++idx)
		{
			auto& it = indexedParent.m_vecChild[idx];
			auto strChild = GenerateSignatureFromIndexedNodeRecurs(it, mapping);
			strArgs += strChild;
			if (idx != indexedParent.m_vecChild.size() - 1)
				strArgs += ", ";
		}
		if (indexedParent.IsBindingTypeTemplate())
		{
			if (indexedParent.m_vecChild.size() > 0 && indexedParent.m_vecChild.back().IsBindingTypeTemplate())
				strArgs += ' ';
			strArgs += '>';
		}

		auto strName = GenerateNamespacesAndScopesCode(subcursor.m_cursorDecl);
		strName += subcursor.GetTypeName();
		return strName + strArgs;
	}
#endif
	//static Niflect::CString MakeSignatureForFieldRecurs(const CBindingAccessorIndexedNode& indexedParent, const CBindingAccessorIndexedNode& childrenOwner, const SResolvingDependenciesContext& ctx, CSignatureCodeMapping& signatureMapping)
	//{
	//	Niflect::CString signature;
	//	auto ret = signatureMapping.m_mapSignatureToIndex.insert({ indexedParent.m_key, static_cast<uint32>(signatureMapping.m_vecCode.size()) });
	//	if (ret.second)
	//	{
	//		if (indexedParent.m_settingIdx != INDEX_NONE)
	//		{
	//			Niflect::CString strArgs;
	//			if (childrenOwner.IsBindingTypeTemplate())
	//				strArgs += '<';
	//			for (uint32 idx = 0; idx < childrenOwner.m_vecChild.size(); ++idx)
	//			{
	//				auto& it = childrenOwner.m_vecChild[idx];
	//				auto strChild = MakeSignatureForFieldRecurs(it, it, ctx, signatureMapping);
	//				strArgs += strChild;
	//				if (idx != childrenOwner.m_vecChild.size() - 1)
	//					strArgs += ", ";
	//			}
	//			if (childrenOwner.IsBindingTypeTemplate())
	//			{
	//				if ((strArgs.size() > 0 && strArgs.back() == '>')//特化无 Children, 但一定以 > 结尾, 同时又兼容生成的模板代码
	//					//|| (childrenOwner.m_vecChild.size() > 0 && childrenOwner.m_vecChild.back().IsBindingTypeTemplate())
	//					)
	//				{
	//					//可加选项决定生成风格, 是否加空格
	//					strArgs += ' ';
	//				}
	//				strArgs += '>';
	//			}
	//			auto& strName = ctx.m_bindingAccessorMapping.m_vecAccessorBindingSetting[indexedParent.m_settingIdx].m_bindingTypePattern;
	//			signature = strName + strArgs;

	//			for (auto& it : childrenOwner.m_vecChild)
	//				MakeSignatureForFieldRecurs(it, it, ctx, signatureMapping);

	//			if (auto next = indexedParent.m_next.Get())
	//				MakeSignatureForFieldRecurs(*next, indexedParent, ctx, signatureMapping);
	//		}
	//		else if (indexedParent.m_taggedIdx != INDEX_NONE)
	//		{
	//			signature = ctx.m_resolvedTaggedTypeMapping.m_vecType[indexedParent.m_taggedIdx]->m_typeNamePattern;
	//			ASSERT(childrenOwner.m_vecChild.size() == 0);
	//			ASSERT(indexedParent.m_next == NULL);
	//		}
	//		else
	//		{
	//			ASSERT(false);
	//		}
	//		signatureMapping.m_vecCode.push_back(CSignatureCode(signature, indexedParent));
	//	}
	//	else
	//	{
	//		signature = signatureMapping.m_vecCode[ret.first->second].m_signatureStr;
	//	}

	//	return signature;
	//}

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

	static Niflect::CString ResolveSignature(const CBindingAccessorIndexedNode& indexedParent, const CResolvingDependenciesContext& ctx, CSignatureCodeMapping& signatureMapping)
	{
		return ResolveSignatureRecurs(indexedParent, indexedParent, ctx, signatureMapping);
	}
	//static void MakeSignatureForClassDecl(const CBindingAccessorIndexedNode& indexedParent, const CResolvedTaggedTypesMapping& mapping, CSignatureCodeMapping& signatureMapping)
	//{
	//	auto ret = signatureMapping.m_mapSignatureToIndex.insert({ indexedParent.m_key, static_cast<uint32>(signatureMapping.m_vecCode.size()) });
	//	ASSERT(ret.second);
	//	auto& signature = mapping.m_vecType[indexedParent.m_taggedIdx]->m_typeNamePattern;
	//	signatureMapping.m_vecCode.push_back(CSignatureCode(signature, indexedParent));
	//}
	void CTaggedInheritableType::ResolveDependcies(const CResolvingDependenciesContext& context, SResolvingDependenciesData& data)
	{
		//基类
		ASSERT(m_baseTaggedType == NULL);
		auto baseTypeCursorDecl = clang_getTypeDeclaration(clang_getCursorType(m_baseTypeSpecifierCursor));
		auto& taggedMapping = context.m_mappings.m_tagged;
		auto itFound = taggedMapping.m_mapCursorToIndex.find(baseTypeCursorDecl);
		if (itFound != taggedMapping.m_mapCursorToIndex.end())
			m_baseTaggedType = taggedMapping.m_vecType[itFound->second];

		//成员变量
		ASSERT(m_vecMember.size() == 0);
		for (auto& it : m_vecChild)
		{
			//嵌套类型也为taggedType的子节点
			if (auto member = CTaggedInheritableTypeMember::CastChecked(it.Get()))
				m_vecMember.push_back(member);
		}

		auto& cursor = this->GetCursor();
		ASSERT(!m_classDeclIndexedRoot.IsValid());
		if (!taggedMapping.InitIndexedNodeForClassDecl(cursor, m_classDeclIndexedRoot))
		{
			ASSERT(false);
		}
		ResolveSignature(m_classDeclIndexedRoot, context, data.m_signatureMapping);

		m_vecMemberIndexedRoot.resize(m_vecMember.size());
		for (uint32 idx0 = 0; idx0 < m_vecMember.size(); ++idx0)
		{
			auto& it0 = m_vecMember[idx0];
			auto& indexedRoot = m_vecMemberIndexedRoot[idx0];
			auto& cursor = it0->GetCursor();
			context.m_mappings.m_accessorBinding.InitIndexedNodeForField(cursor, it0->m_vecDetailCursor, taggedMapping, context.m_mappings.m_untaggedTemplate, indexedRoot);
			if (!indexedRoot.IsValid())
			{
				GenLogError(context.m_log, NiflectUtil::FormatString("The accessor of the member %s::%s is not specified", m_typeNamePattern.c_str(), CXStringToCString(clang_getCursorSpelling(cursor)).c_str()));
				break;
			}
			//DebugPrintIndexedNodeRecurs(indexedRoot, indexedRoot, context.m_bindingAccessorMapping, 0);
			ResolveSignature(indexedRoot, context, data.m_signatureMapping);
		}
	}
	CSharedTypeRegCodeWriter CTaggedInheritableType::Deprecated_CreateCodeWriter(const STypeRegClassWritingSetting& setting) const
	{
		CXCursor baseTypeCursorDecl = g_invalidCursor;
		if (m_baseTaggedType != NULL)
			baseTypeCursorDecl = m_baseTaggedType->GetCursor();
		Niflect::TArrayNif<CTaggedInheritableTypeMember*> vecMember;
		for (auto& it : m_vecChild)
		{
			//嵌套类型也为taggedType的子节点
			if (auto member = CTaggedInheritableTypeMember::CastChecked(it.Get()))
				vecMember.push_back(member);
		}
		return Niflect::MakeShared<CInheritableTypeRegCodeWriter_ObjectAccessor>(this->GetCursor(), setting, baseTypeCursorDecl, vecMember);
	}
	CSharedTypeRegCodeWriter CTaggedInheritableType::CreateCodeWriter(const STypeRegClassWritingSetting& setting) const
	{
		CXCursor baseTypeCursorDecl = g_invalidCursor;
		if (m_baseTaggedType != NULL)
			baseTypeCursorDecl = m_baseTaggedType->GetCursor();
		return Niflect::MakeShared<CInheritableTypeRegCodeWriter_ObjectAccessor>(this->GetCursor(), setting, baseTypeCursorDecl, m_vecMember);
	}
	void CTaggedInheritableType::DebugDerivedPrint(FILE* fp) const
	{
		Niflect::CString baseClassStr;
		const auto& baseTypeCursor = m_baseTypeSpecifierCursor;
		if (clang_Cursor_isNull(baseTypeCursor))
			baseClassStr = "No base class";
		else
			baseClassStr = NiflectUtil::FormatString("Base class name: %s", CXStringToCString(clang_getCursorSpelling(baseTypeCursor)).c_str());
		printf(", %s", baseClassStr.c_str());
	}
}