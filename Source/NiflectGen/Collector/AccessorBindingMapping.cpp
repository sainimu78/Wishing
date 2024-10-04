#include "NiflectGen/Collector/AccessorBindingMapping.h"

namespace NiflectGen
{
	void CAccessorBindingMapping2::IterateForTemplate(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, Niflect::TArrayNif<uint32>& vecFoundIdx, uint32& detailIteratingIdx) const
	{
		auto argsCount = clang_Type_getNumTemplateArguments(fieldOrArgCXType);
		for (int32 idx1 = 0; idx1 < argsCount; ++idx1)
		{
			CXType argType = clang_Type_getTemplateArgumentAsType(fieldOrArgCXType, idx1);
			this->FindBindingTypeRecurs(argType, vecDetailCursor, vecFoundIdx, detailIteratingIdx);
		}
	}
	bool CAccessorBindingMapping2::FindBindingTypesSSSSSSSSSSS(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, uint32& detailIteratingIdx, CFoundResult& result) const
	{
		auto& foundIdx = result.m_foundIdx;
		auto& continuing = result.m_continuing;
		auto& vecFoundIdx = result.m_vecFoundIdx;
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
			while ((detailIteratingIdx++) < vecDetailCursor.size())
			{
				auto& it = vecDetailCursor[detailIteratingIdx];
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
			vecFoundIdx.push_back(foundIdx);
			return true;
		}
		return false;
	}
	void CAccessorBindingMapping2::FindBindingTypeRecurs(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, Niflect::TArrayNif<uint32>& vecFoundIdx, uint32& detailIteratingIdx) const
	{
		CFoundResult result(vecFoundIdx);
		if (this->FindBindingTypesSSSSSSSSSSS(fieldOrArgCXType, vecDetailCursor, detailIteratingIdx, result))
		{
			if (result.m_continuing)
			{
				auto& bindingSetting = m_vecAccessorBindingSetting[result.m_foundIdx];
				auto elemDeclsCount = bindingSetting.GetELementBindingTypeDeclsCount();
				if (elemDeclsCount == 0)
				{
					//模板套特化, Niflect::TArrayNif<Niflect::TArrayNif<bool> >
					this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, vecFoundIdx, detailIteratingIdx);
				}
				else
				{
					//多维BindingType
					for (uint32 idx0 = 0; idx0 < elemDeclsCount; ++idx0)
					{
						auto& elemSubcursor = bindingSetting.GetELementBindingTypeDecl(idx0);
						CFoundResult result2222(vecFoundIdx);
						uint32 aaaa = 0;
						if (!this->FindBindingTypesSSSSSSSSSSS(elemSubcursor.m_CXType, elemSubcursor.m_vecAaaaaaaaaa, aaaa, result2222))
						{
							ASSERT(false);//todo: 报错
							break;
						}
						auto p = &detailIteratingIdx;
						auto idxForRepeatedDetail = detailIteratingIdx;
						if (idx0 > 0)
							p = &idxForRepeatedDetail;
						this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, vecFoundIdx, *p);
					}
				}
			}
		}
	}
	void CAccessorBindingMapping2::FindBindingTypeForField(const CXCursor& fieldCursor, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, Niflect::TArrayNif<uint32>& vecFoundIdx) const
	{
		auto fieldCXType = clang_getCursorType(fieldCursor);
		uint32 detailIteratingIdx = 0;
		this->FindBindingTypeRecurs(fieldCXType, vecDetailCursor, vecFoundIdx, detailIteratingIdx);
	}
}