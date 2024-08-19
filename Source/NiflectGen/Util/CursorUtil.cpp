#include "NiflectGen/Util/CursorUtil.h"
#include "Niflect/NiflectBase.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include <iostream>
#include <algorithm>//for std::replace

namespace NiflectGen
{
	const CXCursor g_invalidCursor = clang_getNullCursor();

	using namespace Niflect;

	Niflect::CString CXStringToCString(const CXString& cxStr)
	{
		Niflect::CString str = clang_getCString(cxStr);
		clang_disposeString(cxStr);
		return str;
	}
	bool FindTagByDisplayName(const CXCursor& cursor, const CString& tagName)
	{
		return NiflectUtil::StartsWith(CXStringToCString(clang_getCursorDisplayName(cursor)), tagName);
	}
	bool FindTagByKindAndDisplayName(const CXCursor& cursor, CXCursorKind kindToFind, const CString& tagName)
	{
		if (clang_getCursorKind(cursor) == kindToFind)
			return FindTagByDisplayName(cursor, tagName);
		return false;
	}

	CXType GetPointerOriginalType(const CXType& pointerType)
	{
		auto originalType = pointerType;
		while (originalType.kind == CXType_Pointer)
			originalType = clang_getPointeeType(originalType);
		return originalType;
	}

	Niflect::CString GetCursorInfoTypeName(const CXCursor& cursor)
	{
		Niflect::CString infoTypeName;
		auto kind = clang_getCursorKind(cursor);
		switch (kind)
		{
		case CXCursor_StructDecl:
			infoTypeName = NiflectGenDefinition::NiflectFramework::InfoTypeName::Struct;
			break;
		case CXCursor_ClassDecl:
			infoTypeName = NiflectGenDefinition::NiflectFramework::InfoTypeName::Class;
			break;
		case CXCursor_EnumDecl:
			infoTypeName = NiflectGenDefinition::NiflectFramework::InfoTypeName::Enum;
			break;
		default:
			ASSERT(false);
			break;
		}
		return infoTypeName;
	}
	Niflect::CString GetNameFromCursorOrTypeDeclaration(const CXCursor& cursor, const CXType& type)
	{
		Niflect::CString name;
		if (clang_getCursorKind(cursor) != CXCursor_NoDeclFound)
			name = CXStringToCString(clang_getCursorSpelling(cursor));
		else
			name = CXStringToCString(clang_getTypeSpelling(type));
		return name;
	}
	Niflect::CString GetNameFromTypeDeclaration(const CXType& type)
	{
		auto cursorDecl = clang_getTypeDeclaration(type);
		return GetNameFromCursorOrTypeDeclaration(cursorDecl, type);
	}
	void VisitCursorRecurs(const CXCursor& handle, const CVisitCallbacks& callbacks)
	{
		auto visitor = [](CXCursor childHandle, CXCursor parentHandle, CXClientData data)
			{
				auto& callbacks = *static_cast<const CVisitCallbacks*>(data);

				VisitCursorRecurs(childHandle, callbacks);

				//if (childHandle.kind == CXCursor_LastPreprocessing)
				//	return CXChildVisit_Break;

				return CXChildVisit_Continue;

				//return CXChildVisit_Recurse;
			};

		if (callbacks.m_EnterFunc != nullptr)
			callbacks.m_EnterFunc(handle);

		clang_visitChildren(handle, visitor, reinterpret_cast<CXClientData>(const_cast<CVisitCallbacks*>(&callbacks)));

		if (callbacks.m_LeaveFunc != nullptr)
			callbacks.m_LeaveFunc(handle);
	}

	static void MytoString(const CXString& str, CString& output)
	{
		output = clang_getCString(str);
		clang_disposeString(str);
	}
	static CString DebugIndentToString(uint32 level, const CString& singleIndentInString = "-")
	{
		auto curLevel = level;
		CString strLevel;
		while (curLevel--)
			strLevel += singleIndentInString;
		return strLevel;
	}
	static bool CXType_IsBuiltinType(CXTypeKind typeKind)
	{
		return (typeKind > CXType_FirstBuiltin && typeKind < CXType_LastBuiltin);
	}
	static void PrintTemplateArguments(const CXCursor& handle)
	{
		if (handle.kind == CXCursor_TypedefDecl)
		{
			CXType typedefType = clang_getCursorType(handle);
			int numTemplateArgs = clang_Type_getNumTemplateArguments(typedefType);
			if (numTemplateArgs > 0)
			{
				for (int i = 0; i < numTemplateArgs; ++i)
				{
					CXType argType = clang_Type_getTemplateArgumentAsType(typedefType, i);
					CString displayName2;
					if (CXType_IsBuiltinType(argType.kind))
					{
						CXString argTypeName = clang_getTypeSpelling(argType);
						displayName2 = clang_getCString(argTypeName);
						clang_disposeString(argTypeName);
					}
					else
					{
						//可打印模板参数, 但自定义的类型无法打印, 自定义类型时cursor为NotFoundDecl
						auto cursor = clang_getTypeDeclaration(argType);
						MytoString(clang_getCursorDisplayName(cursor), displayName2);
					}
					printf("Template argument %d: %s\n", i, displayName2.c_str());
				}
			}
		}
	}
	void FindNamespaceAndScopeNameRecurs(const CXCursor& cursor, Niflect::TArrayNif<Niflect::CString>& vecNamespace, Niflect::TArrayNif<Niflect::CString>& vecScope)
	{
		CXCursor parentCursor;
		if (clang_getCursorKind(cursor) == CXCursor_TemplateRef)
		{
			parentCursor = clang_getCursorReferenced(cursor);
			FindNamespaceAndScopeNameRecurs(parentCursor, vecNamespace, vecScope);
		}
		else
		{
			parentCursor = clang_getCursorSemanticParent(cursor);
		}

		if (clang_getCursorKind(parentCursor) == CXCursor_Namespace)
		{
			FindNamespaceAndScopeNameRecurs(parentCursor, vecNamespace, vecScope);
			vecNamespace.push_back(CXStringToCString(clang_getCursorSpelling(parentCursor)));
		}
		else if (clang_getCursorKind(parentCursor) == CXCursor_ClassDecl)
		{
			FindNamespaceAndScopeNameRecurs(parentCursor, vecNamespace, vecScope);
			vecScope.push_back(CXStringToCString(clang_getCursorSpelling(parentCursor)));
		}
		else if (clang_getCursorKind(parentCursor) == CXCursor_TranslationUnit)
		{
			return;
		}
	}
	void RemoveUnnessesaryNamespacees(const Niflect::TArrayNif<Niflect::CString>& vecNamespaceReference, Niflect::TArrayNif<Niflect::CString>& vecNamespace)
	{
		if (vecNamespace.size() == 0)
			return;
		if (vecNamespaceReference.size() == 0)
			return;
		uint32 commonScopesCount = 0;
		for (uint32 idx = 0; idx < vecNamespaceReference.size(); ++idx)
		{
			if (vecNamespaceReference[idx] == vecNamespace[commonScopesCount])
				commonScopesCount++;
			else
				break;
		}
		if (commonScopesCount == vecNamespaceReference.size())
			vecNamespace.clear();
		else
			vecNamespace.erase(vecNamespace.begin(), vecNamespace.begin() + commonScopesCount);
	}
	bool IsCursorTemplateDecl(const CXCursor& cursor)
	{
		bool isTemplate = false;
		auto kind = clang_getCursorKind(cursor);
		switch (kind)
		{
		case CXCursor_TypeAliasTemplateDecl:
		case CXCursor_ClassTemplate:
			isTemplate = true;
			break;
		default:
			break;
		}
		return isTemplate;
	}
	Niflect::CString GetCursorFilePath(const CXCursor& cursor)
	{
		auto loc = clang_getCursorLocation(cursor);
		CXFile file;
		clang_getSpellingLocation(loc, &file, NULL, NULL, NULL);
		auto filePathAbs = CXStringToCString(clang_getFileName(file));
		std::replace(filePathAbs.begin(), filePathAbs.end(), '\\', '/');
		return filePathAbs;
	}
	void DebugPrintCursor(FILE* fp, const CXCursor& handle, int level)
	{
		auto strLevel = DebugIndentToString(level);

		CString displayName;
		MytoString(clang_getCursorDisplayName(handle), displayName);

		CString strKind;
		{
			CXCursorKind cursorKind = clang_getCursorKind(handle);
			CXString cursorKindSpelling = clang_getCursorKindSpelling(cursorKind);
			strKind = clang_getCString(cursorKindSpelling);
			clang_disposeString(cursorKindSpelling);
		}

		uint32 lineNumber;
		uint32 column;
		uint32 offset;
		const bool showFilePath = false;
		CString filePath;
		{
			CXSourceLocation location = clang_getCursorLocation(handle);
			CXFile file;
			CXFile* pcxFile = NULL;
			if (showFilePath)
				pcxFile = &file;
			clang_getSpellingLocation(location, pcxFile, &lineNumber, &column, &offset);
			if (pcxFile != NULL)
			{
				auto cxStr = clang_getFileName(*pcxFile);
				if (cxStr.data != NULL)
				{
					filePath = clang_getCString(cxStr);
					clang_disposeString(cxStr);
				}
			}
		}

		fprintf(fp, "%s%s, (%s, %u, %u, %u%s)\n", strLevel.c_str(), displayName.c_str(), strKind.c_str(), lineNumber, column, offset, showFilePath ? filePath.c_str() : "");
	}
}