#include "NiflectGen/TaggedType/TaggedInheritableType.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "NiflectGen/CodeWriter/TypeReg/InheritableTypeRegCodeWriter.h"
#include "Niflect/Util/TypeUtil.h"

namespace NiflectGen
{
	CTaggedInheritableType::CTaggedInheritableType()
		: m_baseTypeSpecifierCursor(g_invalidCursor)
		, m_baseTaggedType(NULL)
	{
	}
	void CTaggedInheritableType::InitBaseTypeSpecifierCursor(const CXCursor& cursor)
	{
		ASSERT(clang_Cursor_isNull(m_baseTypeSpecifierCursor));
		m_baseTypeSpecifierCursor = cursor;
	}
	void CTaggedInheritableType::ResolveDependcies(const TCursorMap<CTaggedType*>& mapCursorDeclToTaggedType)
	{
		ASSERT(m_baseTaggedType == NULL);
		auto baseTypeCursorDecl = clang_getTypeDeclaration(clang_getCursorType(m_baseTypeSpecifierCursor));
		auto itFound = mapCursorDeclToTaggedType.find(baseTypeCursorDecl);
		if (itFound != mapCursorDeclToTaggedType.end())
			m_baseTaggedType = itFound->second;
	}
	CSharedTypeRegCodeWriter CTaggedInheritableType::CreateCodeWriter(const STypeRegClassWritingSetting& setting) const
	{
		CXCursor baseTypeCursorDecl = g_invalidCursor;
		if (m_baseTaggedType != NULL)
			baseTypeCursorDecl = m_baseTaggedType->GetCursor();
		Niflect::TArrayNif<CTaggedInheritableTypeMember*> vecMember;
		for (auto& it : m_vecChild)
		{
			//嵌套类型也为taggedType的子节点
			if (auto member = Niflect::CastChecked<CTaggedInheritableTypeMember>(it.Get()))
				vecMember.push_back(member);
		}
		return Niflect::MakeShared<CInheritableTypeRegCodeWriter_ObjectAccessor>(this->GetCursor(), setting, baseTypeCursorDecl, vecMember);
	}
	void CTaggedInheritableType::DebugDerivedPrint(FILE* fp) const
	{
		Niflect::CString baseClassStr;
		const auto& baseTypeCursor = m_baseTypeSpecifierCursor;
		if (clang_Cursor_isNull(baseTypeCursor))
			baseClassStr = "No base class";
		else
			baseClassStr = NiflectUtil::FormatString("Base class name: %s", CXStringToCString(clang_getCursorSpelling(baseTypeCursor)).c_str());
		printf(", %s", baseClassStr.c_str());
	}
}