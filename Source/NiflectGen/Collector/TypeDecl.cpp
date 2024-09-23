#include "NiflectGen/Collector/TypeDecl.h"
#include "Niflect/Util/DebugUtil.h"

namespace NiflectGen
{
	void BuildSubcursorRecursOld(const CXType& parentType, const Niflect::TArrayNif<CXCursor>& vecAAAAAAA, uint32& frontIndex, CSubcursor& parentSubcursor)
	{
		auto cursorDecl = clang_getTypeDeclaration(parentType);

		//auto a = CXStringToCString(clang_getCursorSpelling(cursorDecl));
		//auto b = CXStringToCString(clang_getTypeSpelling(parentType));

		parentSubcursor.m_cursorDecl = cursorDecl;
		parentSubcursor.m_CXType = parentType;

		if (frontIndex < vecAAAAAAA.size())
		{
			if ((clang_getCursorKind(parentSubcursor.m_cursorDecl) != CXCursor_NoDeclFound) || (parentType.kind == CXType_Unexposed))
			{
				while (clang_getCursorKind(vecAAAAAAA[frontIndex]) == CXCursor_NamespaceRef)
				{
					parentSubcursor.m_vecAaaaaaaaaa.push_back(vecAAAAAAA[frontIndex]);
					frontIndex++;
				}
				parentSubcursor.m_vecAaaaaaaaaa.push_back(vecAAAAAAA[frontIndex]);
				frontIndex++;
			}
			else if (parentType.kind == CXType_Invalid)
			{
				while (clang_getCursorKind(vecAAAAAAA[frontIndex]) == CXCursor_NamespaceRef)
				{
					parentSubcursor.m_vecAaaaaaaaaa.push_back(vecAAAAAAA[frontIndex]);
					frontIndex++;
				}
				parentSubcursor.m_vecAaaaaaaaaa.push_back(vecAAAAAAA[frontIndex]);
				frontIndex++;

				parentSubcursor.m_cursorDecl = parentSubcursor.m_vecAaaaaaaaaa.back();
				parentSubcursor.m_CXType = clang_getCursorType(parentSubcursor.m_cursorDecl);
			}
		}

		//if (parentSubcursor.m_vecAaaaaaaaaa.size() > 0)
		//{
		//	auto a = CXStringToCString(clang_getCursorSpelling(parentSubcursor.m_vecAaaaaaaaaa.back()));
		//	auto b = clang_getCursorReferenced(parentSubcursor.m_vecAaaaaaaaaa.back());
		//	auto c = clang_getCursorType(b);
		//	auto d = clang_getTypeDeclaration(c);
		//	auto e = CXStringToCString(clang_getCursorSpelling(b));
		//	auto f = CXStringToCString(clang_getCursorSpelling(d));
		//	auto g = clang_getSpecializedCursorTemplate(parentSubcursor.m_vecAaaaaaaaaa.back());
		//	auto h = CXStringToCString(clang_getTypeSpelling(c));
		//	printf("");
		//}

		auto templateArgsCount = clang_Type_getNumTemplateArguments(parentType);
		if (templateArgsCount > 0)
			parentSubcursor.m_vecChild.resize(templateArgsCount);
		for (int idx = 0; idx < templateArgsCount; ++idx)
		{
			CXType argType = clang_Type_getTemplateArgumentAsType(parentType, idx);
			BuildSubcursorRecursOld(argType, vecAAAAAAA, frontIndex, parentSubcursor.m_vecChild[idx]);
		}
	}
	void BuildSubcursorRecurs2(const CXType& parentType, uint32 maxDepth, const Niflect::TArrayNif<CXCursor>& vecAAAAAAA, uint32& frontIndex, CSubcursor& parentSubcursor, uint32 depth, bool skipAlias)
	{
		auto cursorDecl = clang_getTypeDeclaration(parentType);

		//auto a = CXStringToCString(clang_getCursorSpelling(cursorDecl));
		//auto b = CXStringToCString(clang_getTypeSpelling(parentType));

		if (maxDepth == INDEX_NONE || depth < maxDepth)
		{
			parentSubcursor.m_cursorDecl = cursorDecl;
			parentSubcursor.m_CXType = parentType;

			if (frontIndex < vecAAAAAAA.size())
			{
				bool takingDetail = false;
				if ((clang_getCursorKind(parentSubcursor.m_cursorDecl) != CXCursor_NoDeclFound) || (parentType.kind == CXType_Unexposed))
				{
					takingDetail = true;
				}
				else if (parentType.kind == CXType_Invalid)
				{
					takingDetail = true;
				}
				if (takingDetail)
				{
					while (clang_getCursorKind(vecAAAAAAA[frontIndex]) == CXCursor_NamespaceRef)
					{
						parentSubcursor.m_vecAaaaaaaaaa.push_back(vecAAAAAAA[frontIndex]);
						frontIndex++;
					}
					parentSubcursor.m_vecAaaaaaaaaa.push_back(vecAAAAAAA[frontIndex]);
					frontIndex++;

					//parentSubcursor.m_cursorDecl = parentSubcursor.m_vecAaaaaaaaaa.back();
					//parentSubcursor.m_CXType = clang_getCursorType(parentSubcursor.m_cursorDecl);
				}
			}

			//if (parentSubcursor.m_vecAaaaaaaaaa.size() > 0)
			//{
			//	auto a = CXStringToCString(clang_getCursorSpelling(parentSubcursor.m_vecAaaaaaaaaa.back()));
			//	auto b = clang_getCursorReferenced(parentSubcursor.m_vecAaaaaaaaaa.back());
			//	auto c = clang_getCursorType(b);
			//	auto d = clang_getTypeDeclaration(c);
			//	auto e = CXStringToCString(clang_getCursorSpelling(b));
			//	auto f = CXStringToCString(clang_getCursorSpelling(d));
			//	auto g = clang_getSpecializedCursorTemplate(parentSubcursor.m_vecAaaaaaaaaa.back());
			//	auto h = CXStringToCString(clang_getTypeSpelling(c));
			//	printf("");
			//}
		}

		depth++;

		if (!skipAlias || (clang_getCursorKind(parentSubcursor.m_cursorDecl) != CXCursor_TypeAliasDecl))
		{
			auto templateArgsCount = clang_Type_getNumTemplateArguments(parentType);
			if (templateArgsCount > 0)
			{
				if (maxDepth == INDEX_NONE || depth < maxDepth)
					parentSubcursor.m_vecChild.resize(templateArgsCount);
			}
			for (int idx = 0; idx < templateArgsCount; ++idx)
			{
				CXType argType = clang_Type_getTemplateArgumentAsType(parentType, idx);
				CSubcursor* p = &parentSubcursor;
				if (idx < parentSubcursor.m_vecChild.size())
					p = &parentSubcursor.m_vecChild[idx];
				BuildSubcursorRecurs2(argType, maxDepth, vecAAAAAAA, frontIndex, *p, depth, skipAlias);
			}
		}
	}
	bool BuildSubcursor(const CXType& parentType, const Niflect::TArrayNif<CXCursor>& vecAAAAAAA, CSubcursor& parentSubcursor, bool skipAlias)
	{
		uint32 cursorArrayFrontIndex = 0;
		BuildSubcursorRecurs2(parentType, INDEX_NONE, vecAAAAAAA, cursorArrayFrontIndex, parentSubcursor, 0, skipAlias);
		return cursorArrayFrontIndex == vecAAAAAAA.size();
	}
	void PrintSubcursorRecurs(const CSubcursor& parentSubcursor, uint32 level)
	{
		auto strLevel = NiflectUtil::DebugIndentToString(level);
		auto a = GetNameFromCursorOrTypeDeclaration(parentSubcursor.m_cursorDecl, parentSubcursor.m_CXType);
		Niflect::CString b;
		for (uint32 idx = 0; idx < parentSubcursor.m_vecAaaaaaaaaa.size(); ++idx)
		{
			auto& it = parentSubcursor.m_vecAaaaaaaaaa[idx];
			b += CXStringToCString(clang_getCursorSpelling(it));
			if (idx != parentSubcursor.m_vecAaaaaaaaaa.size() - 1)
				b += "::";
		}
		printf("%s%s, %s\n", strLevel.c_str(), a.c_str(), b.c_str());
		level++;
		for (auto& it : parentSubcursor.m_vecChild)
			PrintSubcursorRecurs(it, level);
	}
	void GenerateTemplateInstanceCodeRecurs(const CSubcursor& parentSubcursor, Niflect::CString& text)
	{
		auto a = GetNameFromCursorOrTypeDeclaration(parentSubcursor.m_cursorDecl, parentSubcursor.m_CXType);
		text += a;
		if (parentSubcursor.m_vecChild.size() > 0)
		{
			text += "<";
			for (uint32 idx = 0; idx < parentSubcursor.m_vecChild.size(); ++idx)
			{
				Niflect::CString childText;
				GenerateTemplateInstanceCodeRecurs(parentSubcursor.m_vecChild[idx], childText);
				text += childText;
				if (idx != parentSubcursor.m_vecChild.size() - 1)
					text += ", ";
			}
			if (parentSubcursor.m_vecChild.back().m_vecChild.size() > 1)
				text += " ";
			text += ">";
		}
	}
	void GenerateTemplateInstanceCodeRecurs2(const CSubcursor& parentSubcursor, Niflect::CString& text, bool& withRightAngleBracket, const Niflect::TArrayNif<Niflect::CString>& vecTemplateArgReplacementString)
	{
		Niflect::CString name;
		if (parentSubcursor.m_vecAaaaaaaaaa.size() > 0)
		{
			for (uint32 idx = 0; idx < parentSubcursor.m_vecAaaaaaaaaa.size(); ++idx)
			{
				auto& it = parentSubcursor.m_vecAaaaaaaaaa[idx];
				auto kind = clang_getCursorKind(it);
				if (clang_isReference(kind))
				{
					auto decl = clang_getCursorReferenced(it);
					name += CXStringToCString(clang_getCursorSpelling(decl));
					if (idx != parentSubcursor.m_vecAaaaaaaaaa.size() - 1)
						name += "::";
				}
				else
				{
					ASSERT(false);
				}
			}
		}
		else
		{
			name = GetNameFromCursorOrTypeDeclaration(parentSubcursor.m_cursorDecl, parentSubcursor.m_CXType);
		}
		text += name;
		bool canRecurs = true;
		if (parentSubcursor.m_vecAaaaaaaaaa.size() > 0)
		{
			//m_vecChild为模板参数所引用的decl, 如TypedefAliasDecl, m_vecAaaaaaaaaa[0]中为模板参数的Spelling类型, 非模板为TypeRef, 模板为TemplateRef, 因此TypeRef不应继续递归
			if (clang_getCursorKind(parentSubcursor.m_vecAaaaaaaaaa[0]) == CXCursor_TypeRef)
			{
				ASSERT(parentSubcursor.m_vecAaaaaaaaaa.size() == 1);
				canRecurs = false;
				withRightAngleBracket = false;
			}
		}
		if ((canRecurs) && (parentSubcursor.m_vecChild.size() > 0))
		{
			bool isLastChildWithRightAngleBracket = false;
			text += "<";
			for (uint32 idx = 0; idx < parentSubcursor.m_vecChild.size(); ++idx)
			{
				Niflect::CString childText;
				if (vecTemplateArgReplacementString.size() > 0)
				{
					ASSERT(vecTemplateArgReplacementString.size() == parentSubcursor.m_vecChild.size());
					childText = vecTemplateArgReplacementString[idx];
					if (childText.back() == '>')
						isLastChildWithRightAngleBracket = true;
				}
				else
				{
					GenerateTemplateInstanceCodeRecurs2(parentSubcursor.m_vecChild[idx], childText, isLastChildWithRightAngleBracket, vecTemplateArgReplacementString);
				}
				text += childText;
				if (idx != parentSubcursor.m_vecChild.size() - 1)
					text += ", ";
			}
			if (isLastChildWithRightAngleBracket)
				text += " ";
			text += ">";
			withRightAngleBracket = true;
		}
	}
	void GenerateTemplateInstanceCode(const CSubcursor& parentSubcursor, Niflect::CString& text, const Niflect::TArrayNif<Niflect::CString>& vecTemplateArgReplacementString)
	{
		bool withRightAngleBracket = false;
		GenerateTemplateInstanceCodeRecurs2(parentSubcursor, text, withRightAngleBracket, vecTemplateArgReplacementString);
	}
}