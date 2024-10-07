#pragma once
#include "Niflect/NiflectBase.h"
#include "NiflectGen/Collector/TypeDecl.h"
#include "NiflectGen/Collector/AccessorData.h"
#include "NiflectGen/Util/CursorMap.h"

namespace NiflectGen
{
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
	};

#ifdef EMBEDDING_ELEMENT_BINDING_TYPE_INDEXED_NODE
	class CBindingAccessorIndexedNode;
	using CSharedBindingAccessorIndexedNode = Niflect::TSharedPtr<CBindingAccessorIndexedNode>;
#else
#endif

	class CBindingAccessorIndexedNode
	{
	public:
		CBindingAccessorIndexedNode()
			: m_settingIdx(INDEX_NONE)
			, m_taggedIdx(INDEX_NONE)
		{
		}
		void InitForTemplateBegin(uint32 foundIdx);
		void InitForTemplateArguments(const CBindingAccessorIndexedNode& childrenOwner);
		void InitForTemplateEnd();
		void InitForTemplate(uint32 foundIdx, const CBindingAccessorIndexedNode& childrenOwner);
		void InitForClassDecl(uint32 foundIdx);
		bool IsBindingTypeTemplate() const
		{
			return m_vecChild.size() > 0;
		}
		bool IsValid() const
		{
			return m_settingIdx != INDEX_NONE || m_taggedIdx != INDEX_NONE;
		}
		uint32 m_settingIdx;
		uint32 m_taggedIdx;
		Niflect::TArrayNif<CBindingAccessorIndexedNode> m_vecChild;
		Niflect::CString m_key;
#ifdef EMBEDDING_ELEMENT_BINDING_TYPE_INDEXED_NODE
		CSharedBindingAccessorIndexedNode m_next;
#else
#endif
	};

	class CFoundResult
	{
	public:
		CFoundResult(CBindingAccessorIndexedNode& indexedParent)
			: m_indexedParent(indexedParent)
			, m_foundIdx(INDEX_NONE)
			, m_continuing(true)
		{
		}
		CBindingAccessorIndexedNode& m_indexedParent;
		uint32 m_foundIdx;
		bool m_continuing;
	};

	class CAccessorBindingMapping2
	{
	public:
		void FindBindingTypeForField(const CXCursor& fieldCursor, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, CBindingAccessorIndexedNode& resultIndexedParent) const;

	private:
		void IterateForTemplate(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, CBindingAccessorIndexedNode& resultIndexedParent, uint32& detailIteratingIdx) const;
		bool FindBindingTypesSSSSSSSSSSS(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, uint32& detailIteratingIdx, CFoundResult& result) const;
		void FindBindingTypeRecurs(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, CBindingAccessorIndexedNode& resultIndexedParent, uint32& detailIteratingIdx) const;

	public:
		Niflect::TArrayNif<CBindingSettingData> m_vecAccessorBindingSetting;
		TCursorMap<uint32> m_mapCursorToIndex;
		TCXTypeMap<uint32> m_mapCXTypeToIndex;
		TCursorMap<uint32> m_mapSpecializedCursorToIndex;
	};
	using CSharedAccessorBindingMapping = Niflect::TSharedPtr<CAccessorBindingMapping2>;

	void MakeKeyForClassDecl(CBindingAccessorIndexedNode& resultIndexedParent, uint32 foundIdx);
}