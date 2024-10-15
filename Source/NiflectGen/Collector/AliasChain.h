#pragma once
#include "NiflectGen/Util/CursorMap.h"

namespace NiflectGen
{
	class CAliasChain
	{
	public:
		void AddLinkDecl(const CXCursor& decl);
		void LinkToReferenced(const CXCursor& decl, const CXCursor& alias);
		CXCursor FindOriginalDeclOld(CXCursor decl) const;
		bool FindOriginalDecl(CXCursor decl, CXCursor& lastValidDecl) const;

	private:
		TCursorMap<CXCursor> m_mapDeclToReferenced;
	};
	using CSharedAliasChain = Niflect::TSharedPtr<CAliasChain>;
}