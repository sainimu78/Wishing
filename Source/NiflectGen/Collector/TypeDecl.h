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
		Niflect::TArrayNif<CXCursor> m_vecAaaaaaaaaa;//todo: 计划改名为m_vecDetailCursor
		Niflect::TArrayNif<CSubcursor> m_vecChild;
	};

	//void BuildSubcursorRecursOld(const CXType& parentType, const Niflect::TArrayNif<CXCursor>& vecAAAAAAA, uint32& frontIndex, CSubcursor& parentSubcursor);
	//void BuildSubcursorRecurs2(const CXType& parentType, uint32 maxDepth, const Niflect::TArrayNif<CXCursor>& vecAAAAAAA, uint32& frontIndex, CSubcursor& parentSubcursor, uint32 depth = 0);
	bool BuildSubcursor(const CXType& parentType, const Niflect::TArrayNif<CXCursor>& vecAAAAAAA, CSubcursor& parentSubcursor, bool skipAlias = false);
	void PrintSubcursorRecurs(const CSubcursor& parentSubcursor, uint32 level = 0);

	class CGenerateTemplateInstanceCodeOption
	{
		using CThis = CGenerateTemplateInstanceCodeOption;
	public:
		CGenerateTemplateInstanceCodeOption()
			: m_vecTemplateArgReplacementString(NULL)
			, m_withFullScope(false)
		{

		}
		CThis& SetWithFullScope(bool b)
		{
			m_withFullScope = b;
			return *this;
		}
		const Niflect::TArrayNif<Niflect::CString>* m_vecTemplateArgReplacementString;
		bool m_withFullScope;
	};
	void GenerateTemplateInstanceCode(const CSubcursor& parentSubcursor, Niflect::CString& text, const CGenerateTemplateInstanceCodeOption& opt = CGenerateTemplateInstanceCodeOption());

	Niflect::CString GenerateFullScopeTypeName(const CSubcursor& bSubcursor);
}