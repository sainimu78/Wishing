#include "NiflectGen/Collector/TaggedNode.h"
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Util/DebugUtil.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "NiflectGen/Log/Log.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"

namespace NiflectGen
{
	using namespace Niflect;

	static CString GetMacroExpansionArgsInString(const CXCursor& cursor)
	{
		CString result;
		CXSourceRange range = clang_getCursorExtent(cursor);
		CXToken* tokens = nullptr;
		unsigned int numTokens = 0;
		CXTranslationUnit translationUnit = clang_Cursor_getTranslationUnit(cursor);
		clang_tokenize(translationUnit, range, &tokens, &numTokens);

		for (unsigned i = 0; i < numTokens; ++i)
		{
			CXString spelling = clang_getTokenSpelling(translationUnit, tokens[i]);
			result += clang_getCString(spelling);
			clang_disposeString(spelling);
		}

		clang_disposeTokens(translationUnit, tokens, numTokens);
		return result;
	}

	bool CXSourceLocationComp::operator()(const CXSourceLocation& lhs, const CXSourceLocation& rhs) const
	{
		//// Use Clang API to compare source locations. Assume `isEqual` returns
		//// true if the two source locations are equal.
		//if (clang_equalLocations(lhs, rhs)) {
		//	return false; // Equal locations, so lhs is not less than rhs
		//}

		// Compare the source locations by their respective data.
		// clang_getExpansionLocation could be used to get file, line, column, and offset data.
		CXFile lhs_file, rhs_file;
		unsigned lhs_line, lhs_column, lhs_offset;
		unsigned rhs_line, rhs_column, rhs_offset;

		//现只用于macroExpansion的cursor查找, 但不确认是否有必要用clang_getExpansionLocation, 
		//clang_getExpansionLocation(lhs, &lhs_file, &lhs_line, &lhs_column, &lhs_offset);
		//clang_getExpansionLocation(rhs, &rhs_file, &rhs_line, &rhs_column, &rhs_offset);
		clang_getSpellingLocation(lhs, &lhs_file, &lhs_line, &lhs_column, &lhs_offset);
		clang_getSpellingLocation(rhs, &rhs_file, &rhs_line, &rhs_column, &rhs_offset);

		// Prioritize by file, then line, then column, then offset
		if (lhs_file != rhs_file) {
			return lhs_file < rhs_file;
		}
		else if (lhs_line != rhs_line) {
			return lhs_line < rhs_line;
		}
		else if (lhs_column != rhs_column) {
			return lhs_column < rhs_column;
		}
		return lhs_offset < rhs_offset;
	}

	CMacroTagCollection2::CMacroTagCollection2()
	{

	}
	CMacroTagCollection2::~CMacroTagCollection2()
	{
	}
#ifdef SIMPLIFIED_MACRO_CURSOR_FINDING
	bool CMacroTagCollection2::PushMacroExpansion(CXCursorKind kind, const CXCursor& cursor)
	{
		if (kind == CXCursor_MacroExpansion)
		{
			m_stkMacroCursor.push_back(cursor);
			return true;
		}
		return false;
	}
	void CMacroTagCollection2::PopMacroExpansion(CXCursor& macroCursor)
	{
		auto it = m_stkMacroCursor.begin();
		it += m_stkMacroCursor.size() - 1;
		m_stkMacroCursor.erase(it);
	}
#else
	bool CMacroTagCollection2::CollectMacroExpansion(const CXCursor& cursor)
	{
		auto kind = clang_getCursorKind(cursor);
		if (kind == CXCursor_MacroExpansion)
		{
			auto loc = clang_getCursorLocation(cursor);
			auto ret = m_mapLocationToMacroCursor.insert({ loc, cursor });
			if (ret.second)
			{
			}
			else
			{
				ASSERT(false);//不应出现重复loc
			}
			return true;
		}
		return false;
	}
	void CMacroTagCollection2::TakeByTagLocation(const CXSourceLocation& tagLocation, CXCursor& macroCursor)
	{
		auto itFound = m_mapLocationToMacroCursor.find(tagLocation);
		if (itFound != m_mapLocationToMacroCursor.end())
		{
			macroCursor = itFound->second;
			m_mapLocationToMacroCursor.erase(itFound);
		}
		else
		{
			ASSERT(false);
		}
	}
#endif

	CTaggedNode2::CTaggedNode2()
		: m_cursor(g_invalidCursor)
		, m_macroCursor(g_invalidCursor)
	{

	}
	void CTaggedNode2::Init(const CXCursor& cursor)
	{
		m_cursor = cursor;
	}
	void CTaggedNode2::AddChildAndInitDefault(const CSharedTaggedNode& taggedNode, const CXCursor& cursor, const CXCursor& macroCursor)
	{
		taggedNode->Init(cursor);
		taggedNode->SetMacroCursor(macroCursor);
		m_vecChild.push_back(taggedNode);
	}
	void CTaggedNode2::DebugPrint(FILE* fp, uint32 level) const
	{
		auto strLevel = NiflectUtil::DebugIndentToString(level);

		//if (IsCursorNeededFindingTaggedType(clang_getCursorKind(it.m_typeCursor)))
		{
			auto typeName = CXStringToCString(clang_getCursorSpelling(m_cursor));
			auto macroName = CXStringToCString(clang_getCursorSpelling(m_macroCursor));
			auto macroArgs = GetMacroExpansionArgsInString(m_macroCursor);

			//if (!clang_Cursor_isNull(it.m_typeCursor))
			{
				auto strCursorKind = CXStringToCString(clang_getCursorKindSpelling(clang_getCursorKind(m_cursor)));
				printf("%s%s, %s, %s, %s", strLevel.c_str(), strCursorKind.c_str(), typeName.c_str(), macroName.c_str(), macroArgs.c_str());
				this->DebugDerivedPrint(fp);
				printf("\n");
			}
		}
	}
}