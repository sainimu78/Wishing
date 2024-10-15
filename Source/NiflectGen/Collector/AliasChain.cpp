#include "NiflectGen/Collector/AliasChain.h"
#include "NiflectGen/Util/CursorUtil.h"

namespace NiflectGen
{
	void CAliasChain::AddLinkDecl(const CXCursor& decl)
	{
		m_mapDeclToReferenced.insert({ decl, g_invalidCursor });
	}
	void CAliasChain::LinkToReferenced(const CXCursor& decl, const CXCursor& alias)
	{
		auto itFound = m_mapDeclToReferenced.find(decl);
		if (itFound != m_mapDeclToReferenced.end())
			itFound->second = clang_getCursorReferenced(alias);
	}
	CXCursor CAliasChain::FindOriginalDeclOld(CXCursor decl) const
	{
		CXCursor lastValidDecl = decl;
		while (true)
		{
			auto a = CXStringToCString(clang_getCursorSpelling(decl));
			auto templateDecl = clang_getSpecializedCursorTemplate(decl);
			if (!clang_Cursor_isNull(templateDecl))
				decl = templateDecl;
			if (!IsCursorAliasDecl(decl))
				return decl;
			auto itFound = m_mapDeclToReferenced.find(decl);
			if (itFound != m_mapDeclToReferenced.end())
				decl = itFound->second;
			else
				break;
			if (clang_Cursor_isNull(decl))
				break;
			lastValidDecl = decl;
		}
		return lastValidDecl;
	}

	//bool CAliasChain::FindOriginalDecl(CXCursor decl, CXCursor& lastValidDecl) const
	//{
	//	CXCursor lastValidDecl = decl;
	//	bool same = true;
	//	while (true)
	//	{
	//		auto a = CXStringToCString(clang_getCursorSpelling(decl));
	//		auto templateDecl = clang_getSpecializedCursorTemplate(decl);
	//		if (!clang_Cursor_isNull(templateDecl))
	//		{
	//			decl = templateDecl;
	//			same = false;
	//		}
	//		if (!IsCursorAliasDecl(decl))
	//		{
	//			lastValidDecl = decl;
	//			break;
	//		}
	//		auto itFound = m_mapDeclToReferenced.find(decl);
	//		if (itFound != m_mapDeclToReferenced.end())
	//		{
	//			decl = itFound->second;
	//			same = false;
	//		}
	//		else
	//		{
	//			break;
	//		}
	//		if (clang_Cursor_isNull(decl))
	//			break;
	//		lastValidDecl = decl;
	//		same = false;
	//	}
	//	return same;
	//}

	bool CAliasChain::FindOriginalDecl(CXCursor decl, CXCursor& lastValidDecl) const
	{
		lastValidDecl = decl;
		bool diff = false;
		while (true)
		{
			auto a = CXStringToCString(clang_getCursorSpelling(decl));
			auto templateDecl = clang_getSpecializedCursorTemplate(decl);
			if (!clang_Cursor_isNull(templateDecl))
			{
				decl = templateDecl;
				if (!IsCursorAliasDecl(decl))
				{
					lastValidDecl = decl;
					diff = true;
					break;
				}
			}
			else
			{
				if (!IsCursorAliasDecl(decl))
				{
					lastValidDecl = decl;
					break;
				}
			}
			auto itFound = m_mapDeclToReferenced.find(decl);
			if (itFound != m_mapDeclToReferenced.end())
				decl = itFound->second;
			else
				break;
			if (clang_Cursor_isNull(decl))
				break;
			lastValidDecl = decl;
			diff = true;
		}
		return diff;
	}
}