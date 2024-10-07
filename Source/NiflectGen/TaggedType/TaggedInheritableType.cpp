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

		if (auto next = indexedParent.m_next.Get())
		{
			lv--;
			printf("---------------\n");
			DebugPrintIndexedNodeRecurs(*next, indexedParent, mapping, lv);
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
	static Niflect::CString NSSSSSSSSS(const CXCursor& cursor, const CXType& type)
	{
		Niflect::CString name;
		auto kind = clang_getCursorKind(cursor);
		if ((kind != CXCursor_NoDeclFound) && (kind != CXCursor_ClassDecl))
		{
			name = GenerateNamespacesAndScopesCode(cursor);
			name += CXStringToCString(clang_getCursorSpelling(cursor));
		}
		else
		{
			name = CXStringToCString(clang_getTypeSpelling(type));
		}
		return name;
	}
	//static Niflect::CString GenerateSignatureFromIndexedNodeRecurs(const CBindingAccessorIndexedNode& indexedParent, const CBindingAccessorIndexedNode& childrenOwner, const CAccessorBindingMapping2& mapping, Niflect::TArrayNif<Niflect::CString>& vecSignature)
	//{
	//	if (auto next = indexedParent.m_next.Get())
	//		GenerateSignatureFromIndexedNodeRecurs(*next, indexedParent, mapping, vecSignature);

	//	Niflect::CString strArgs;
	//	if (childrenOwner.IsBindingTypeTemplate())
	//		strArgs += '<';
	//	for (uint32 idx = 0; idx < childrenOwner.m_vecChild.size(); ++idx)
	//	{
	//		auto& it = childrenOwner.m_vecChild[idx];
	//		auto strChild = GenerateSignatureFromIndexedNodeRecurs(it, it, mapping, vecSignature);
	//		strArgs += strChild;
	//		if (idx != childrenOwner.m_vecChild.size() - 1)
	//			strArgs += ", ";
	//	}
	//	if (childrenOwner.IsBindingTypeTemplate())
	//	{
	//		if ((strArgs.size() > 0 && strArgs.back() == '>')//特化无 Children, 但一定以 > 结尾, 同时又兼容生成的模板代码
	//			//|| (childrenOwner.m_vecChild.size() > 0 && childrenOwner.m_vecChild.back().IsBindingTypeTemplate())
	//			)
	//		{
	//			//可加选项决定生成风格, 是否加空格
	//			strArgs += ' ';
	//		}
	//		strArgs += '>';
	//	}

	//	auto& subcursor = mapping.m_vecAccessorBindingSetting[indexedParent.m_settingIdx].GetBindingTypeDecl();
	//	auto strName = NSSSSSSSSS(subcursor.m_cursorDecl, subcursor.m_CXType);
	//	auto signature = strName + strArgs;
	//	vecSignature.push_back(signature);
	//	return signature;
	//}
	static Niflect::CString MakeSignatureForFieldRecurs(const CBindingAccessorIndexedNode& indexedParent, const CBindingAccessorIndexedNode& childrenOwner, const CAccessorBindingMapping2& mapping, CSignatureCodeMapping& signatureMapping)
	{
		Niflect::CString signature;
		auto ret = signatureMapping.m_mapSignatureToIndex.insert({ indexedParent.m_key, static_cast<uint32>(signatureMapping.m_vecCode.size())});
		if (ret.second)
		{
			Niflect::CString strArgs;
			if (childrenOwner.IsBindingTypeTemplate())
				strArgs += '<';
			for (uint32 idx = 0; idx < childrenOwner.m_vecChild.size(); ++idx)
			{
				auto& it = childrenOwner.m_vecChild[idx];
				auto strChild = MakeSignatureForFieldRecurs(it, it, mapping, signatureMapping);
				strArgs += strChild;
				if (idx != childrenOwner.m_vecChild.size() - 1)
					strArgs += ", ";
			}
			if (childrenOwner.IsBindingTypeTemplate())
			{
				if ((strArgs.size() > 0 && strArgs.back() == '>')//特化无 Children, 但一定以 > 结尾, 同时又兼容生成的模板代码
					//|| (childrenOwner.m_vecChild.size() > 0 && childrenOwner.m_vecChild.back().IsBindingTypeTemplate())
					)
				{
					//可加选项决定生成风格, 是否加空格
					strArgs += ' ';
				}
				strArgs += '>';
			}
			auto& subcursor = mapping.m_vecAccessorBindingSetting[indexedParent.m_settingIdx].GetBindingTypeDecl();
			auto strName = NSSSSSSSSS(subcursor.m_cursorDecl, subcursor.m_CXType);
			signature = strName + strArgs;
			signatureMapping.m_vecCode.push_back(CSignatureCode(signature));
		}
		else
		{
			signature = signatureMapping.m_vecCode[ret.first->second].m_signatureStr;
		}

		for (auto& it : childrenOwner.m_vecChild)
			MakeSignatureForFieldRecurs(it, it, mapping, signatureMapping);

		if (auto next = indexedParent.m_next.Get())
			MakeSignatureForFieldRecurs(*next, indexedParent, mapping, signatureMapping);

		return signature;
	}
	static void MakeSignatureForClassDecl(const CBindingAccessorIndexedNode& indexedParent, const CResolvedTaggedTypesMapping& mapping, CSignatureCodeMapping& signatureMapping)
	{
		auto ret = signatureMapping.m_mapSignatureToIndex.insert({ indexedParent.m_key, static_cast<uint32>(signatureMapping.m_vecCode.size()) });
		ASSERT(ret.second);
		auto& cursor = mapping.m_vecType[indexedParent.m_taggedIdx]->GetCursor();
		auto signature = GenerateNamespacesAndScopesCode(cursor);
		signature += CXStringToCString(clang_getCursorSpelling(cursor));
		signatureMapping.m_vecCode.push_back(CSignatureCode(signature));
	}
	void CTaggedInheritableType::ResolveDependcies(const SResolvingDependenciesContext& context, SResolvingDependenciesData& data)
	{
		//基类
		ASSERT(m_baseTaggedType == NULL);
		auto baseTypeCursorDecl = clang_getTypeDeclaration(clang_getCursorType(m_baseTypeSpecifierCursor));
		auto itFound = context.m_resolvedTaggedTypeMapping.m_mapCursorToIndex.find(baseTypeCursorDecl);
		if (itFound != context.m_resolvedTaggedTypeMapping.m_mapCursorToIndex.end())
			m_baseTaggedType = context.m_resolvedTaggedTypeMapping.m_vecType[itFound->second];

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
		if (!context.m_resolvedTaggedTypeMapping.FindForClassDecl(cursor, m_classDeclIndexedRoot))
		{
			ASSERT(false);
		}
		MakeSignatureForClassDecl(m_classDeclIndexedRoot, context.m_resolvedTaggedTypeMapping, data.m_signatureMapping);

		m_vecMemberIndexedRoot.resize(m_vecMember.size());
		for (uint32 idx0 = 0; idx0 < m_vecMember.size(); ++idx0)
		{
			auto& it0 = m_vecMember[idx0];
			auto& indexedRoot = m_vecMemberIndexedRoot[idx0];
			auto& dddd = it0->GetCursor();
			context.m_bindingAccessorMapping.FindBindingTypeForField(dddd, it0->m_vecDetailCursor, indexedRoot);
			ASSERT(indexedRoot.IsValid());
			//DebugPrintIndexedNodeRecurs(indexedRoot, indexedRoot, context.m_bindingAccessorMapping, 0);
			MakeSignatureForFieldRecurs(indexedRoot, indexedRoot, context.m_bindingAccessorMapping, data.m_signatureMapping);
			for (auto& it1 : data.m_signatureMapping.m_vecCode)
				printf("=%s=\n", it1.m_signatureStr.c_str());
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