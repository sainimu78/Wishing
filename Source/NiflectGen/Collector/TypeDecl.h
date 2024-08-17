#pragma once
#include "NiflectGen/Util/CursorUtil.h"

namespace NiflectGen
{
	class CTypeDecl
	{
	public:
		CTypeDecl()
			: m_cursorDecl(g_invalidCursor)
			, m_CXType{ CXType_Invalid }
		{

		}
		CTypeDecl(const CXCursor& cursorDecl)
			: m_cursorDecl(cursorDecl)
			, m_CXType{ CXType_Invalid }
		{
		}
		CTypeDecl(const CXType& inCXType)
			: m_cursorDecl(g_invalidCursor)
			, m_CXType(inCXType)
		{
		}
		CTypeDecl(const CXCursor& cursorDecl, const CXType& inCXType)
			: m_cursorDecl(cursorDecl)
			, m_CXType(inCXType)
		{
		}
		Niflect::CString GetTypeName() const
		{
			return GetNameFromCursorOrTypeDeclaration(m_cursorDecl, m_CXType);
		}
		CXCursor m_cursorDecl;
		CXType m_CXType;
	};

	class CSubcursor : public CTypeDecl
	{
	public:
		CSubcursor()
		{
		}
		Niflect::TArrayNif<CXCursor> m_vecAaaaaaaaaa;
		Niflect::TArrayNif<CSubcursor> m_vecChild;
	};

	//void BuildSubcursorRecursOld(const CXType& parentType, const Niflect::TArrayNif<CXCursor>& vecAAAAAAA, uint32& frontIndex, CSubcursor& parentSubcursor);
	//void BuildSubcursorRecurs2(const CXType& parentType, uint32 maxDepth, const Niflect::TArrayNif<CXCursor>& vecAAAAAAA, uint32& frontIndex, CSubcursor& parentSubcursor, uint32 depth = 0);
	bool BuildSubcursor(const CXType& parentType, const Niflect::TArrayNif<CXCursor>& vecAAAAAAA, CSubcursor& parentSubcursor, bool skipAlias = false);
	void PrintSubcursorRecurs(const CSubcursor& parentSubcursor, uint32 level = 0);
	void GenerateTemplateInstanceCodeRecurs(const CSubcursor& parentSubcursor, Niflect::CString& text);
	void GenerateTemplateInstanceCode(const CSubcursor& parentSubcursor, Niflect::CString& text);
}