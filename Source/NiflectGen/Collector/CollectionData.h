#pragma once
#include "NiflectGen/Util/CursorMap.h"
#include "NiflectGen/Collector/AccessorBindingMapping.h"

namespace NiflectGen
{
	class CAliasChain
	{
	public:
		void AddLinkDecl(const CXCursor& decl);
		void LinkToReferenced(const CXCursor& decl, const CXCursor& alias);
		CXCursor FindOriginalDecl(CXCursor decl) const;

	private:
		TCursorMap<CXCursor> m_mapDeclToReferenced;
	};
	using CSharedAliasChain = Niflect::TSharedPtr<CAliasChain>;

	class CCollectionData
	{
	public:
		Niflect::TArrayNif<CBindingSettingData> deprecated_m_vecBindingSetting;
		TCursorMap<CXCursor> deprecated_m_mapAliasTemplateDeclToClassTemplateCursor;
		CSharedAliasChain m_aliasChain;
		CSharedAccessorBindingMapping m_accessorBindingMapping;
	};
}