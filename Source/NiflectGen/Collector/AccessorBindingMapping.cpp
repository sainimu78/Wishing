#include "NiflectGen/Collector/AccessorBindingMapping.h"

namespace NiflectGen
{
	void CAccessorBindingMapping2::IterateForTemplate(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CResolvedTaggedTypesMapping& resolvedTaggedTypeMapping, CBindingAccessorIndexedNode& resultIndexedParent, uint32& detailIteratingIdx) const
	{
		//auto argsCount = clang_Type_getNumTemplateArguments(fieldOrArgCXType);
		//for (int32 idx1 = 0; idx1 < argsCount; ++idx1)
		//{
		//	CXType argType = clang_Type_getTemplateArgumentAsType(fieldOrArgCXType, idx1);
		//	CBindingAccessorIndexedNode indexedChild;
		//	this->FindBindingTypeRecurs(argType, vecDetailCursor, resolvedTaggedTypeMapping, indexedChild, detailIteratingIdx);
		//	resultIndexedParent.m_vecChild.push_back(indexedChild);
		//}

		auto argsCount = clang_Type_getNumTemplateArguments(fieldOrArgCXType);
		ASSERT(!resultIndexedParent.m_isTemplateFormat);
		resultIndexedParent.m_isTemplateFormat = argsCount > 0;
		for (int32 idx1 = 0; idx1 < argsCount; ++idx1)
		{
			CXType argType = clang_Type_getTemplateArgumentAsType(fieldOrArgCXType, idx1);
			CBindingAccessorIndexedNode* indexedChild = NULL;
			if (argsCount > 1)
			{
				resultIndexedParent.m_vecChild.push_back(CBindingAccessorIndexedNode());
				indexedChild = &resultIndexedParent.m_vecChild.back();
			}
			else
			{
				//����������ʽ�����Ƿ�Ϊ�ṹģ��, ���ṹģ���ģ�����ȷʵΪ1��ʱ, ���̴���, ����Ϊ�б�Ҫ֧��1��ģ������Ľṹģ��, Ӧʹ��һ�����ַ�ʽ, ��ͨ���� UntaggedType ���в����Ƿ�����Ӧģ����, ��ģ�����������ͬ, ����϶�Ϊ�ṹģ��
				resultIndexedParent.m_next = Niflect::MakeShared<CBindingAccessorIndexedNode>();
				indexedChild = resultIndexedParent.m_next.Get();
			}
			this->FindBindingTypeRecurs(argType, vecDetailCursor, resolvedTaggedTypeMapping, *indexedChild, detailIteratingIdx);
		}
	}
	bool CAccessorBindingMapping2::FindBindingTypesSSSSSSSSSSS(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, uint32& detailIteratingIdx, CFoundResult& result) const
	{
		auto& foundIdx = result.m_foundIdx;
		auto& continuing = result.m_continuing;
		auto& indexedParent = result.m_indexedParent;
		{
			auto itFound = m_mapCXTypeToIndex.find(fieldOrArgCXType);
			if (itFound != m_mapCXTypeToIndex.end())
				foundIdx = itFound->second;
		}
		if (foundIdx == INDEX_NONE)
		{
			//�ػ�, <Niflect::TArrayNif<bool>, ��ֱ��ͨ��field����CXType��cursor���ҵ�BindingType��cursor
			auto cursor = clang_getTypeDeclaration(fieldOrArgCXType);
			auto itFound = m_mapSpecializedCursorToIndex.find(cursor);
			if (itFound != m_mapSpecializedCursorToIndex.end())
			{
				foundIdx = itFound->second;
				continuing = false;
			}
		}
		if (foundIdx == INDEX_NONE)
		{
			const CXCursor* refCursor = NULL;
			while (detailIteratingIdx < vecDetailCursor.size())
			{
				auto& it = vecDetailCursor[detailIteratingIdx];
				detailIteratingIdx++;
				auto kind = clang_getCursorKind(it);
				//�����׸��ɴ��������͵�Ref
				if (kind == CXCursor_TemplateRef || kind == CXCursor_TypeRef)
				{
					refCursor = &it;
					break;
				}
			}
			if (refCursor != NULL)
			{
				auto cursor = clang_getCursorReferenced(*refCursor);
				auto itFound = m_mapCursorToIndex.find(cursor);
				if (itFound != m_mapCursorToIndex.end())
				{
					foundIdx = itFound->second;
					continuing = IsCursorTemplateDecl(cursor);
				}
			}
		}
		if (foundIdx != INDEX_NONE)
		{
			indexedParent.m_settingIdx = foundIdx;
			return true;
		}
		return false;
	}
	void CBindingAccessorIndexedNode::InitForTemplateBegin(const Niflect::CString& signature, uint32 foundIdx)
	{
		ASSERT(m_key.empty());
		m_key += '(';
		m_key += std::to_string(foundIdx).c_str();

		ASSERT(m_signature.empty());
		m_signature = signature;
	}
	//static void SADSAF(Niflect::TArrayNif<const CBindingAccessorIndexedNode*>& vec, Niflect::CString& str)
	//{
	//	if (vec.size() == 0)
	//	{
	//		return;
	//	}
	//	else
	//	{
	//		str += vec.back()->m_signature;
	//		vec.pop_back();
	//	}
	//	SADSAF(vec, str);
	//	str += '>';
	//}
	void CBindingAccessorIndexedNode::InitForTemplateArguments(const CBindingAccessorIndexedNode& childrenOwner)
	{
		if (auto next = childrenOwner.m_next.Get())
		{
			m_key += next->m_key;
			ASSERT(childrenOwner.m_vecChild.size() == 0);
		}
		else
		{
			for (auto& it : childrenOwner.m_vecChild)
				m_key += it.m_key;
		}
		if (childrenOwner.IsTemplateFormat())
		{
			m_signature += '<';
			Niflect::TArrayNif<const CBindingAccessorIndexedNode*> vec;
			const CBindingAccessorIndexedNode* p = childrenOwner.m_next.Get();
			if (p != NULL)
			{
				ASSERT(childrenOwner.m_vecChild.size() == 0);
				m_signature += p->m_signature;
			}
			else
			{
				for (uint32 idx = 0; idx < childrenOwner.m_vecChild.size(); ++idx)
				{
					m_signature += childrenOwner.m_vecChild[idx].m_signature;
					if (idx != childrenOwner.m_vecChild.size() - 1)
						m_signature += ", ";
				}
			}
			if (m_signature.back() == '>')
				m_signature += ' ';
			m_signature += '>';
		}
	}
	void CBindingAccessorIndexedNode::InitForTemplateEnd()
	{
		m_key += ')';
	}
	void CBindingAccessorIndexedNode::InitForTemplate(const Niflect::CString& signature, uint32 foundIdx, const CBindingAccessorIndexedNode& childrenOwner)
	{
		this->InitForTemplateBegin(signature, foundIdx);
		this->InitForTemplateArguments(childrenOwner);
		this->InitForTemplateEnd();
	}
	void CBindingAccessorIndexedNode::InitForClassDecl(const Niflect::CString& signature, uint32 foundIdx)
	{
		ASSERT(m_key.empty());
		m_key += '[';
		m_key += std::to_string(foundIdx).c_str();
		m_key += ']';
		m_taggedIdx = foundIdx;

		ASSERT(m_signature.empty());
		m_signature = signature;
	}
	void CAccessorBindingMapping2::FindBindingTypeRecurs(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CResolvedTaggedTypesMapping& resolvedTaggedTypeMapping, CBindingAccessorIndexedNode& resultIndexedParent, uint32& detailIteratingIdx) const
	{
		CFoundResult result(resultIndexedParent);
		if (this->FindBindingTypesSSSSSSSSSSS(fieldOrArgCXType, vecDetailCursor, detailIteratingIdx, result))
		{
			resultIndexedParent.InitForTemplateBegin(m_vecAccessorBindingSetting[result.m_foundIdx].m_bindingTypePattern, result.m_foundIdx);

			if (result.m_continuing)
			{
				//auto& bindingSetting = m_vecAccessorBindingSetting[result.m_foundIdx];
				////ģ�����ػ��� BindingType, ��Ա������ Niflect::TArrayNif<Niflect::TArrayNif<bool> >
				//this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, resolvedTaggedTypeMapping, resultIndexedParent, detailIteratingIdx);
				//resultIndexedParent.InitForTemplateArguments(resultIndexedParent);

				//auto elemDeclsCount = bindingSetting.GetELementBindingTypeDeclsCount();
				//if (elemDeclsCount > 0)
				//{
				//	auto pIndexedParent = &resultIndexedParent;
				//	//��ά BindingType, ����͵� TStlMapAccessor ����, ��0άΪ TMap, ��1άΪ sd::pair
				//	for (uint32 idx0 = 0; idx0 < elemDeclsCount; ++idx0)
				//	{
				//		auto& elemSubcursor = bindingSetting.GetELementBindingTypeDecl(idx0);
				//		pIndexedParent->m_next = Niflect::MakeShared<CBindingAccessorIndexedNode>();
				//		pIndexedParent = pIndexedParent->m_next.Get();
				//		CFoundResult result2222(*pIndexedParent);
				//		uint32 aaaa = 0;
				//		if (!this->FindBindingTypesSSSSSSSSSSS(elemSubcursor.m_CXType, elemSubcursor.m_vecAaaaaaaaaa, aaaa, result2222))
				//		{
				//			ASSERT(false);//todo: ����, ÿάBindingType����Ҫָ��AccessorType
				//			break;
				//		}
				//		pIndexedParent->InitForTemplate(m_vecAccessorBindingSetting[result2222.m_foundIdx].m_bindingTypePattern, result2222.m_foundIdx, resultIndexedParent);
				//	}
				//}



				auto& bindingSetting = m_vecAccessorBindingSetting[result.m_foundIdx];

				auto elemDeclsCount = bindingSetting.GetELementBindingTypeDeclsCount();
				if (elemDeclsCount > 0)
				{
					auto pIndexedParent = &resultIndexedParent;
					//��ά BindingType, ����͵� TStlMapAccessor ����, ��0άΪ TMap, ��1άΪ sd::pair
					Niflect::TArrayNif<std::pair<CBindingAccessorIndexedNode*, uint32> > vecSSSSSSSSS;
					for (uint32 idx0 = 0; idx0 < elemDeclsCount; ++idx0)
					{
						auto& elemSubcursor = bindingSetting.GetELementBindingTypeDecl(idx0);
						pIndexedParent->m_next = Niflect::MakeShared<CBindingAccessorIndexedNode>();
						pIndexedParent = pIndexedParent->m_next.Get();
						CFoundResult result2222(*pIndexedParent);
						uint32 aaaa = 0;
						if (!this->FindBindingTypesSSSSSSSSSSS(elemSubcursor.m_CXType, elemSubcursor.m_vecAaaaaaaaaa, aaaa, result2222))
						{
							ASSERT(false);//todo: ����, ÿάBindingType����Ҫָ��AccessorType
							break;
						}
						//pIndexedParent->InitForTemplate(m_vecAccessorBindingSetting[result2222.m_foundIdx].m_bindingTypePattern, result2222.m_foundIdx, resultIndexedParent);
						vecSSSSSSSSS.push_back({ pIndexedParent, result2222.m_foundIdx });
					}
					this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, resolvedTaggedTypeMapping, *pIndexedParent, detailIteratingIdx);
					resultIndexedParent.InitForTemplateArguments(*pIndexedParent);

					for (auto& it : vecSSSSSSSSS)
					{
						auto& foundIdx = it.second;
						it.first->InitForTemplate(m_vecAccessorBindingSetting[foundIdx].m_bindingTypePattern, foundIdx, *pIndexedParent);
					}
				}
				else
				{
					//ģ�����ػ��� BindingType, ��Ա������ Niflect::TArrayNif<Niflect::TArrayNif<bool> >
					this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, resolvedTaggedTypeMapping, resultIndexedParent, detailIteratingIdx);
					resultIndexedParent.InitForTemplateArguments(resultIndexedParent);
				}
			}
			resultIndexedParent.InitForTemplateEnd();
		}
		else
		{
			auto cursor = clang_getTypeDeclaration(fieldOrArgCXType);
			resolvedTaggedTypeMapping.InitIndexedNodeForClassDecl(cursor, resultIndexedParent);
		}
	}
	void CAccessorBindingMapping2::InitIndexedNodeForField(const CXCursor& fieldCursor, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CResolvedTaggedTypesMapping& resolvedTaggedTypeMapping, CBindingAccessorIndexedNode& resultIndexedParent) const
	{
		auto fieldCXType = clang_getCursorType(fieldCursor);
		uint32 detailIteratingIdx = 0;
		this->FindBindingTypeRecurs(fieldCXType, vecDetailCursor, resolvedTaggedTypeMapping, resultIndexedParent, detailIteratingIdx);
	}
	void CAccessorBindingMapping2::InitPatterns()
	{
		for (auto& it : m_vecAccessorBindingSetting)
		{
			auto& bSubcursor = it.GetBindingTypeDecl();
			it.m_bindingTypePattern = NSSSSSSSSS(bSubcursor.m_cursorDecl, bSubcursor.m_CXType);
		}
	}
}