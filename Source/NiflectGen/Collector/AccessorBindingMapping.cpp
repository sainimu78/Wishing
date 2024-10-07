#include "NiflectGen/Collector/AccessorBindingMapping.h"

namespace NiflectGen
{
	void CAccessorBindingMapping2::IterateForTemplate(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, CBindingAccessorIndexedNode& resultIndexedParent, uint32& detailIteratingIdx) const
	{
		auto argsCount = clang_Type_getNumTemplateArguments(fieldOrArgCXType);
		for (int32 idx1 = 0; idx1 < argsCount; ++idx1)
		{
			CXType argType = clang_Type_getTemplateArgumentAsType(fieldOrArgCXType, idx1);
			CBindingAccessorIndexedNode indexedChild;
			this->FindBindingTypeRecurs(argType, vecDetailCursor, indexedChild, detailIteratingIdx);
			resultIndexedParent.m_vecChild.push_back(indexedChild);
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
			//特化, <Niflect::TArrayNif<bool>, 可直接通过field本身CXType的cursor查找到BindingType的cursor
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
				//查找首个可处理的类型的Ref
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
	void CBindingAccessorIndexedNode::InitForTemplateBegin(uint32 foundIdx)
	{
		ASSERT(m_key.empty());
		m_key += '(';
		m_key += std::to_string(foundIdx).c_str();
	}
	void CBindingAccessorIndexedNode::InitForTemplateArguments(const CBindingAccessorIndexedNode& childrenOwner)
	{
		for (auto& it : childrenOwner.m_vecChild)
			m_key += it.m_key;
	}
	void CBindingAccessorIndexedNode::InitForTemplateEnd()
	{
		m_key += ')';
	}
	void CBindingAccessorIndexedNode::InitForTemplate(uint32 foundIdx, const CBindingAccessorIndexedNode& childrenOwner)
	{
		this->InitForTemplateBegin(foundIdx);
		this->InitForTemplateArguments(childrenOwner);
		this->InitForTemplateEnd();
	}
	void CBindingAccessorIndexedNode::InitForClassDecl(uint32 foundIdx)
	{
		ASSERT(m_key.empty());
		m_key += '[';
		m_key += std::to_string(foundIdx).c_str();
		m_key += ']';
		m_taggedIdx = foundIdx;
	}
	void CAccessorBindingMapping2::FindBindingTypeRecurs(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, CBindingAccessorIndexedNode& resultIndexedParent, uint32& detailIteratingIdx) const
	{
		CFoundResult result(resultIndexedParent);
		if (!this->FindBindingTypesSSSSSSSSSSS(fieldOrArgCXType, vecDetailCursor, detailIteratingIdx, result))
		{
			ASSERT(false);//todo: 报错, 每维BindingType都需要指定AccessorType
		}

		resultIndexedParent.InitForTemplateBegin(result.m_foundIdx);

		if (result.m_continuing)
		{

#ifdef EMBEDDING_ELEMENT_BINDING_TYPE_INDEXED_NODE
			auto& bindingSetting = m_vecAccessorBindingSetting[result.m_foundIdx];
			//模板套特化的 BindingType, 成员类型如 Niflect::TArrayNif<Niflect::TArrayNif<bool> >
			this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, resultIndexedParent, detailIteratingIdx);
			resultIndexedParent.InitForTemplateArguments(resultIndexedParent);

			auto elemDeclsCount = bindingSetting.GetELementBindingTypeDeclsCount();
			if (elemDeclsCount > 0)
			{
				auto pIndexedParent = &resultIndexedParent;
				//多维 BindingType, 如典型的 TStlMapAccessor 设置, 第0维为 TMap, 第1维为 sd::pair
				for (uint32 idx0 = 0; idx0 < elemDeclsCount; ++idx0)
				{
					auto& elemSubcursor = bindingSetting.GetELementBindingTypeDecl(idx0);
					pIndexedParent->m_next = Niflect::MakeShared<CBindingAccessorIndexedNode>();
					pIndexedParent = pIndexedParent->m_next.Get();
					CFoundResult result2222(*pIndexedParent);
					uint32 aaaa = 0;
					if (!this->FindBindingTypesSSSSSSSSSSS(elemSubcursor.m_CXType, elemSubcursor.m_vecAaaaaaaaaa, aaaa, result2222))
					{
						ASSERT(false);//todo: 报错, 每维BindingType都需要指定AccessorType
						break;
					}
					pIndexedParent->InitForTemplate(result2222.m_foundIdx, resultIndexedParent);
				}
			}
#else
			auto& bindingSetting = m_vecAccessorBindingSetting[result.m_foundIdx];
			auto elemDeclsCount = bindingSetting.GetELementBindingTypeDeclsCount();
			auto pIndexedParent = &resultIndexedParent;
			if (elemDeclsCount > 0)
			{
				//多维 BindingType, 如典型的 TStlMapAccessor 设置, 第0维为 TMap, 第1维为 sd::pair
				for (uint32 idx0 = 0; idx0 < elemDeclsCount; ++idx0)
				{
					auto& elemSubcursor = bindingSetting.GetELementBindingTypeDecl(idx0);
					pIndexedParent->m_vecChild.push_back(CBindingAccessorIndexedNode());
					pIndexedParent = &pIndexedParent->m_vecChild.back();
					CFoundResult result2222(*pIndexedParent);
					uint32 aaaa = 0;
					if (!this->FindBindingTypesSSSSSSSSSSS(elemSubcursor.m_CXType, elemSubcursor.m_vecAaaaaaaaaa, aaaa, result2222))
					{
						ASSERT(false);//todo: 报错, 每维BindingType都需要指定AccessorType
						break;
					}
				}
			}
			//模板套特化的 BindingType, 成员类型如 Niflect::TArrayNif<Niflect::TArrayNif<bool> >
			this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, *pIndexedParent, detailIteratingIdx);
#endif
		}
		resultIndexedParent.InitForTemplateEnd();
	}
	void CAccessorBindingMapping2::FindBindingTypeForField(const CXCursor& fieldCursor, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, CBindingAccessorIndexedNode& resultIndexedParent) const
	{
		auto fieldCXType = clang_getCursorType(fieldCursor);
		uint32 detailIteratingIdx = 0;
		this->FindBindingTypeRecurs(fieldCXType, vecDetailCursor, resultIndexedParent, detailIteratingIdx);
	}
}