#pragma once
#include "NiflectGen/Util/CursorMap.h"
#include "NiflectGen/Collector/CollectionData.h"
#include "NiflectGen/TaggedType/TaggedType.h"

namespace NiflectGen
{
	class CResolvedTaggedType
	{
	public:
		CResolvedTaggedType()
			: m_taggedType(NULL)
			//, m_isBuiltinType(false)
		{

		}
		CResolvedTaggedType(CTaggedType* taggedType)
			: m_taggedType(taggedType)
			//, m_isBuiltinType(false)
		{

		}
		CTaggedType* m_taggedType;
		//bool m_isBuiltinType;
	};

	class CFieldWWWWWWW
	{
	public:
		CFieldWWWWWWW(const CSubcursor& subcursor)
			: m_untaggedType(NULL)
			, m_subcursor(subcursor)
		{

		}
		CTaggedType* m_untaggedType;
		CSubcursor m_subcursor;
	};

	class CAccessorBinding
	{
	public:
		CAccessorBinding(const CXCursor& accessorCursorDecl, const CXCursor& actualFieldDeclCursor, const CAccessorData& accessorData)
			: m_accessorCursorDecl(accessorCursorDecl)
			, m_actualFieldDeclCursor(actualFieldDeclCursor)
			, m_accessorTaggedType(NULL)
			, m_accessorData(accessorData)
		{
		}
		bool Is1D() const
		{
			return m_vecWWWW.size() == 1;
		}
		bool Is2D() const
		{
			return m_vecWWWW.size() == 2;
		}
		CXCursor m_accessorCursorDecl;
		CXCursor m_actualFieldDeclCursor;
		CTaggedType* m_accessorTaggedType;
		Niflect::TArrayNif<CFieldWWWWWWW> m_vecWWWW;
		CAccessorData m_accessorData;
	};

	struct SAccessorBindingIndexAndBasicBindingCXType
	{
		uint32 m_accessorBindingIndex;
		CXType m_CXType;
	};

	class CAccessorBindingMapping
	{
	public:
		//const CAccessorBinding* FindByTypeElaborated(const CXType& type, bool& isTemplate) const
		//{
		//	auto cursorDecl = clang_getTypeDeclaration(type);
		//	auto templateDecl = clang_getSpecializedCursorTemplate(cursorDecl);//cursor为FieldDecl时, template实例的成员cursorDecl仍为ClassDecl, 因此使用该函数获取BindingSetting中注册的类型为TemplateDecl的cursorDecl
		//	if (!clang_Cursor_isNull(templateDecl))
		//	{
		//		cursorDecl = templateDecl;
		//		isTemplate = true;
		//	}
		//	if (clang_getCursorKind(cursorDecl) != CXCursor_NoDeclFound)
		//		return this->FindByCursorDecl(cursorDecl);
		//	return this->FindByCXType(type);
		//}
		const CAccessorBinding* FindByCXType(const CXType& type) const
		{
			auto itFound = m_mapBasicTypeKindToAccessorBindingIndex.find(type.kind);
			if (itFound != m_mapBasicTypeKindToAccessorBindingIndex.end())
				return &m_vecAccessorBinding2[itFound->second.m_accessorBindingIndex];
			return NULL;
		}
		const CAccessorBinding* FindByCursorDecl(const CXCursor& cursorDecl) const
		{
			auto itFound = m_mapBasicCusorDeclToAccessorBindingIndex.find(cursorDecl);
			if (itFound != m_mapBasicCusorDeclToAccessorBindingIndex.end())
				return &m_vecAccessorBinding2[itFound->second];
			return NULL;
		}
		Niflect::TArrayNif<CAccessorBinding> m_vecAccessorBinding2;
		Niflect::TMap<CXTypeKind, SAccessorBindingIndexAndBasicBindingCXType> m_mapBasicTypeKindToAccessorBindingIndex;
		TCursorMap<uint32> m_mapBasicCusorDeclToAccessorBindingIndex;
	};

	class CResolvedMapping
	{
	public:
		CAccessorBindingMapping m_accessorBindingMapping;
		TCursorMap<CTaggedType*> m_mapCursorDeclToTaggedType;
		TCursorMap<CUntaggedTemplate*> m_mapCursorDeclToUntaggedTemplate;
	};

	class CResolvedData
	{
	public:
		////Niflect::TArrayNif<SResolvedType> m_vecResolvedType;//由于解析时已按照用户的BindingSetting.h中include DFS, 因此builtin类型的accessor一定在其它依赖builtin类型的类型之前
		//Niflect::TArrayNif<CResolvedTypes> m_vecResolvedTypes;//由于解析时已按照用户的BindingSetting.h中include DFS, 因此builtin类型的accessor一定在其它依赖builtin类型的类型之前
		//CAccessorTypeTable m_accessorTypeTable;
		//TCursorMap<CTaggedType*> m_mapDeclarationToTaggedType;

		Niflect::TArrayNif<CResolvedTaggedType> m_vecResolvedTypes2;
		//Niflect::TArrayNif<CAccessorBinding> m_vecAccessorBinding;
		//TCursorMap<CTaggedType*> m_mapCusorDeclToTaggedType;
		CResolvedMapping m_mapping;
	};
}