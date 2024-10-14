#pragma once
#include "Niflect/NiflectBase.h"
#include "NiflectGen/Collector/TypeDecl.h"
#include "NiflectGen/Collector/AccessorData.h"
#include "NiflectGen/Util/CursorMap.h"
#include "NiflectGen/Resolver/ResocursorNode.h"

namespace NiflectGen
{
	class CTaggedType;
	class CUntaggedTemplate;
	class CTaggedTypesMapping;

	class CUntaggedTemplateTypesMapping
	{
	public:
		TCursorMap<uint32> m_mapCursorToIndex;
		Niflect::TArrayNif<CUntaggedTemplate*> m_vecType;
	};

	class CBindingSettingData
	{
		enum ESetting
		{
			Field,
			BindingTypeChildStartIndex,
			ElementBindingTypeChildStartIndex,
			Count,
		};
	public:
		CBindingSettingData()
			: deprecated_m_accessorBaseCursorDecl(g_invalidCursor)
			, m_actualFieldDeclCursor(g_invalidCursor)
		{
		}
		const CSubcursor& GetAccessorTypeDecl() const//todo: 计划改名为GetAccessorTypeSubcursor
		{
			return m_subcursorRoot.m_vecChild[Field];
		}
		const CSubcursor& GetBindingTypeDecl() const//todo: 计划改名为GetBindingTypeSubcursor
		{
			return m_subcursorRoot.m_vecChild[BindingTypeChildStartIndex];
		}
		uint32 GetBindingTypeDeclsCount() const//todo: 计划改名为GetDimensionalBindingTypeSubcursorsCount
		{
			return static_cast<uint32>(m_subcursorRoot.m_vecChild.size()) - BindingTypeChildStartIndex;
		}
		const CSubcursor& GetBindingTypeDecl(uint32 idx) const//todo: 计划改名为GetDimensionalBindingTypeSubcursor
		{
			return m_subcursorRoot.m_vecChild[BindingTypeChildStartIndex + idx];
		}
		uint32 GetELementBindingTypeDeclsCountOld() const
		{
			return static_cast<uint32>(m_subcursorRoot.m_vecChild.size()) - ElementBindingTypeChildStartIndex;
		}
		const CSubcursor& GetElementBindingTypeDeclOld(uint32 idx) const
		{
			return m_subcursorRoot.m_vecChild[ElementBindingTypeChildStartIndex + idx];
		}
		uint32 GetELementBindingTypeDeclsCount() const
		{
			return static_cast<uint32>(m_subcursorRoot.m_vecChild.size()) - ElementBindingTypeChildStartIndex;
		}
		const CSubcursor& GetELementBindingTypeDecl(uint32 idx) const
		{
			return m_subcursorRoot.m_vecChild[ElementBindingTypeChildStartIndex + idx];
		}
		bool IsValidBindingSetting() const
		{
			bool valid = false;
			if (m_subcursorRoot.m_vecChild.size() >= ElementBindingTypeChildStartIndex && m_subcursorRoot.m_vecChild.size() <= Count)
				valid = true;
			return valid;
		}

	public:
		CXCursor deprecated_m_accessorBaseCursorDecl;
		CXCursor m_actualFieldDeclCursor;//todo: 应废弃, 改为通过aliasChain查找
		CSubcursor m_subcursorRoot;
		CAccessorData m_accessorData;//todo: 应废弃, 改为通过AccessorBindingMapping查找并获取对应信息
		Niflect::CString m_bindingTypeCursorName;
		Niflect::CString m_accessorTypeCursorName;
	};

	class CFoundResult
	{
	public:
		CFoundResult(CResolvedCursorNode& indexedParent)
			: m_indexedParent(indexedParent)
			, m_foundIdx(INDEX_NONE)
			, m_continuing(true)
		{
		}
		CResolvedCursorNode& m_indexedParent;
		uint32 m_foundIdx;
		bool m_continuing;
	};

	class CAccessorBindingMapping2
	{
	public:
		void InitPatterns();
		void InitIndexedNodeForField(const CXCursor& fieldCursor, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplateTypesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent) const;

	private:
		bool IterateForTemplate(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplateTypesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent, uint32& detailIteratingIdx) const;
		bool FindBindingTypesSSSSSSSSSSS(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, uint32& detailIteratingIdx, CFoundResult& result) const;
		void FindBindingTypeRecurs(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplateTypesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent, uint32& detailIteratingIdx) const;

		void GenerateCursorName(const CXCursor& fieldCursor, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplateTypesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent) const;
		void GenerateCursorNameRecurs(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplateTypesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent, uint32& detailIteratingIdx) const;

	public:
		Niflect::TArrayNif<CBindingSettingData> m_vecAccessorBindingSetting;
		TCursorMap<uint32> m_mapCursorToIndex;
		TCXTypeMap<uint32> m_mapCXTypeToIndex;
		TCursorMap<uint32> m_mapSpecializedCursorToIndex;//包括特化模板与TaggedType对应的类型
	};
	using CSharedAccessorBindingMapping = Niflect::TSharedPtr<CAccessorBindingMapping2>;

	struct SResolvedMappings
	{
		const CAccessorBindingMapping2& m_accessorBinding;
		const CTaggedTypesMapping& m_tagged;
		const CUntaggedTemplateTypesMapping& m_untaggedTemplate;
	};
}