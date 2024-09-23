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
	const Niflect::TArrayNif<CBindingSettingData>* g_debug0 = NULL;
	CSharedTypeRegCodeWriter CTaggedInheritableType::CreateCodeWriter(const STypeRegClassWritingSetting& setting) const
	{
		TCXTypeMap<uint32> mapCXTypeToIndex;
		for (uint32 idx = 0; idx < g_debug0->size(); ++idx)
		{
			if (!mapCXTypeToIndex.insert({ (*g_debug0)[idx].m_subcursorRoot.m_vecChild[1].m_CXType, idx }).second)
				ASSERT(false);
		}
		TCursorMap<uint32> mapCursorToIndex;
		for (uint32 idx = 0; idx < g_debug0->size(); ++idx)
		{
			auto cursor = clang_getTypeDeclaration((*g_debug0)[idx].m_subcursorRoot.m_vecChild[1].m_CXType);
			if (clang_getCursorKind(cursor) != CXCursor_NoDeclFound)
			{
				auto c = CXStringToCString(clang_getCursorSpelling(cursor));

				if (!mapCursorToIndex.insert({ cursor, idx }).second)
					ASSERT(false);
			}
		}

		for (uint32 idx0 = 0; idx0 < m_vecChild.size(); ++idx0)
		{
			auto& it0 = m_vecChild[idx0];
			auto& fieldCursor = it0->GetCursor();
			auto a = CXStringToCString(clang_getCursorSpelling(fieldCursor));
			auto fieldCXType = clang_getCursorType(fieldCursor);
			auto b = CXStringToCString(clang_getTypeSpelling(fieldCXType));
			auto typeRefCursor = clang_getTypeDeclaration(fieldCXType);
			auto typeRefCursorKind = clang_getCursorKind(typeRefCursor);
			auto c = CXStringToCString(clang_getCursorSpelling(typeRefCursor));
			printf("%s, %s, %s\n", a.c_str(), b.c_str(), c.c_str());

			auto& vec1 = *g_debug0;
			//uint32 foundIdx1 = INDEX_NONE;
			//for (uint32 idx1 = 0; idx1 < vec1.size(); ++idx1)
			//{
			//	auto& it1 = vec1[idx1];
			//	auto& bindingCXType = it1.m_subcursorRoot.m_vecChild[1].m_CXType;
			//	if (clang_equalTypes(fieldCXType, bindingCXType))
			//	{
			//		ASSERT(foundIdx1 == INDEX_NONE);
			//		foundIdx1 = idx1;
			//	}
			//}

			//if (foundIdx1 != INDEX_NONE)
			//{
			//	auto& found1 = vec1[foundIdx1];
			//	printf("");
			//}

			{
				//特化, <Niflect::TArrayNif<bool>, 可直接通过field本身CXType的cursor查找到BindingType的cursor
				auto itFound = mapCursorToIndex.find(typeRefCursor);
				if (itFound != mapCursorToIndex.end())
				{
					auto underlyingType = clang_getCursorType(fieldCursor);
					auto d2 = clang_getTypeDeclaration(underlyingType);
					if ((!clang_Cursor_isNull(d2)) && clang_getCursorKind(d2) != CXCursor_NoDeclFound)
					{
						ASSERT(clang_equalCursors(typeRefCursor, d2));

						//通过该函数获取到的cursor是实际定义的cursor, 实际定义是std::vector, 因此查找到的结果是错的
						auto d3 = clang_getSpecializedCursorTemplate(d2);
						auto itFound2 = mapCursorToIndex.find(d3);
						if (itFound2 != mapCursorToIndex.end())
						{
							auto& found1 = vec1[itFound2->second];
							auto& bindingCursor = clang_getTypeDeclaration(found1.m_subcursorRoot.m_vecChild[0].m_CXType);
							auto d = CXStringToCString(clang_getCursorSpelling(bindingCursor));
							printf("");
						}
					}

					auto& found1 = vec1[itFound->second];
					auto& bindingCursor = clang_getTypeDeclaration(found1.m_subcursorRoot.m_vecChild[0].m_CXType);
					auto d = CXStringToCString(clang_getCursorSpelling(bindingCursor));
					printf("");
				}
			}

			{
				//模板套特化, Niflect::TArrayNif<Niflect::TArrayNif<bool> >
				auto cnt1 = clang_Type_getNumTemplateArguments(fieldCXType);
				for (int32 idx1 = 0; idx1 < cnt1; ++idx1)
				{
					CXType argType = clang_Type_getTemplateArgumentAsType(fieldCXType, idx1);
					auto argCursor = clang_getTypeDeclaration(argType);
					auto aaa = CXStringToCString(clang_getTypeSpelling(argType));

					{
						auto itFound = mapCXTypeToIndex.find(argType);
						if (itFound != mapCXTypeToIndex.end())
						{
							ASSERT(false);//不能通过argType找到特化
							auto& found1 = vec1[itFound->second];
							auto& bindingCXType = found1.m_subcursorRoot.m_vecChild[1].m_CXType;
							auto d = CXStringToCString(clang_getTypeSpelling(bindingCXType));
							auto typeRefCursor = clang_getTypeDeclaration(bindingCXType);
							auto e = CXStringToCString(clang_getCursorSpelling(typeRefCursor));
							printf("");
						}
					}
					{
						auto itFound = mapCursorToIndex.find(argCursor);
						if (itFound != mapCursorToIndex.end())
						{
							auto& found1 = vec1[itFound->second];
							auto& bindingCursor = clang_getTypeDeclaration(found1.m_subcursorRoot.m_vecChild[0].m_CXType);
							auto d = CXStringToCString(clang_getCursorSpelling(bindingCursor));
							printf("");
						}
					}
					printf("");
				}
			}

			{
				if (auto member = dynamic_cast<CTaggedInheritableTypeMember*>(it0.Get()))
				{
					//if (member->m_vecDetailCursor.size() > 0)
					//{
					//	//ASSERT(clang_isReference(member->m_vecDetailCursor[0].kind));
					//	//auto c = clang_getCursorReferenced(member->m_vecDetailCursor[0]);
					//	//if (clang_getCursorKind(c) == CXCursor_TypeAliasDecl)
					//	//{
					//	//	auto d = clang_getCursorType(c);
					//	//	auto ddddd = CXStringToCString(clang_getTypeSpelling(d));
					//	//	c = clang_getTypeDeclaration(d);
					//	//	auto itFound = mapCursorToIndex.find(c);
					//	//	if (itFound != mapCursorToIndex.end())
					//	//	{
					//	//		auto& found1 = vec1[itFound->second];
					//	//		auto& bindingCursor = clang_getTypeDeclaration(found1.m_subcursorRoot.m_vecChild[0].m_CXType);
					//	//		auto d = CXStringToCString(clang_getCursorSpelling(bindingCursor));
					//	//		printf("");
					//	//	}
					//	//}

					//	ASSERT(clang_isReference(member->m_vecDetailCursor[0].kind));
					//	auto c = clang_getCursorReferenced(member->m_vecDetailCursor[0]);
					//	if (clang_getCursorKind(c) == CXCursor_TypeAliasDecl)
					//	{
					//		auto d = clang_getCursorType(c);
					//		auto ddddd = CXStringToCString(clang_getTypeSpelling(d));
					//		c = clang_getCursorReferenced(c);
					//		d = clang_getCursorType(c);
					//		ddddd = CXStringToCString(clang_getTypeSpelling(d));
					//		auto itFound = mapCursorToIndex.find(c);
					//		if (itFound != mapCursorToIndex.end())
					//		{
					//			auto& found1 = vec1[itFound->second];
					//			auto& bindingCursor = clang_getTypeDeclaration(found1.m_subcursorRoot.m_vecChild[0].m_CXType);
					//			auto d = CXStringToCString(clang_getCursorSpelling(bindingCursor));
					//			printf("");
					//		}
					//	}
					//}
					if (member->m_vecDetailCursor.size() > 1)
					{
						ASSERT(clang_isReference(member->m_vecDetailCursor[1].kind));
						auto c = clang_getCursorReferenced(member->m_vecDetailCursor[1]);
						//auto aaa = CXStringToCString(clang_getCursorSpelling(c));

						//auto ddddd = clang_getCursorType(c);
						//auto ffff = clang_getCursorType(member->m_vecDetailCursor[1]);

						//auto d = clang_getSpecializedCursorTemplate(typeRefCursor);
						//if ((!clang_Cursor_isNull(d)) && clang_getCursorKind(d) != CXCursor_NoDeclFound)
						//{
						//	//auto aadda = CXStringToCString(clang_getCursorSpelling(d));
						//	//auto dddddd = clang_getCursorType(d);
						//	//auto dfasdf = CXStringToCString(clang_getTypeSpelling(dddddd));
						//	ASSERT(clang_equalCursors(c, d));
						//}

						auto itFound = mapCursorToIndex.find(c);
						if (itFound != mapCursorToIndex.end())
						{
							auto& found1 = vec1[itFound->second];
							auto& bindingCursor = clang_getTypeDeclaration(found1.m_subcursorRoot.m_vecChild[0].m_CXType);
							auto d = CXStringToCString(clang_getCursorSpelling(bindingCursor));
							printf("");
						}
					}
					//if (member->m_vecDetailCursor.size() > 1)
					//{
					//	ASSERT(clang_isReference(member->m_vecDetailCursor[3].kind));
					//	auto c = clang_getCursorReferenced(member->m_vecDetailCursor[3]);
					//	//auto d = clang_getSpecializedCursorTemplate(typeRefCursor);
					//	//if ((!clang_Cursor_isNull(d)) && clang_getCursorKind(d) != CXCursor_NoDeclFound)
					//	//{
					//	//	c = d;
					//	//}
					//	auto dddd = clang_getCursorType(c);

					//	auto itFound = mapCursorToIndex.find(c);
					//	if (itFound != mapCursorToIndex.end())
					//	{
					//		auto& found1 = vec1[itFound->second];
					//		auto& bindingCursor = clang_getTypeDeclaration(found1.m_subcursorRoot.m_vecChild[0].m_CXType);
					//		auto d = CXStringToCString(clang_getCursorSpelling(bindingCursor));
					//		printf("");
					//	}
					//}
				}
			}

			{
				auto itFound = mapCXTypeToIndex.find(fieldCXType);
				if (itFound != mapCXTypeToIndex.end())
				{
					auto& found1 = vec1[itFound->second];
					auto& bindingCXType = found1.m_subcursorRoot.m_vecChild[1].m_CXType;
					auto d = CXStringToCString(clang_getTypeSpelling(bindingCXType));
					auto typeRefCursor = clang_getTypeDeclaration(bindingCXType);
					auto e = CXStringToCString(clang_getCursorSpelling(typeRefCursor));
					printf("");
				}
			}

			//{
			//	if (typeRefCursorKind == CXCursor_ClassDecl)
			//	{
			//		auto templateCursor = clang_getSpecializedCursorTemplate(typeRefCursor);
			//		auto templateCursorKind = clang_getCursorKind(templateCursor);
			//		if ((templateCursorKind != CXCursor_FirstInvalid) && (templateCursorKind != CXCursor_NoDeclFound))
			//		{
			//			typeRefCursor = templateCursor;
			//			typeRefCursorKind = templateCursorKind;

			//			auto d = CXStringToCString(clang_getCursorSpelling(typeRefCursor));
			//			printf("");
			//		}
			//	}

			//	auto itFound = mapCursorToIndex.find(typeRefCursor);
			//	if (itFound != mapCursorToIndex.end())
			//	{
			//		auto& found1 = vec1[itFound->second];
			//		auto& bindingCursor = clang_getTypeDeclaration(found1.m_subcursorRoot.m_vecChild[1].m_CXType);
			//		auto d = CXStringToCString(clang_getCursorSpelling(bindingCursor));
			//		printf("");
			//	}
			//}
		}

		CXCursor baseTypeCursorDecl = g_invalidCursor;
		if (m_baseTaggedType != NULL)
			baseTypeCursorDecl = m_baseTaggedType->GetCursor();
		Niflect::TArrayNif<CTaggedInheritableTypeMember*> vecMember;
		for (auto& it : m_vecChild)
		{
			//嵌套类型也为taggedType的子节点
			if (auto member = CTaggedInheritableTypeMember::CastChecked(it.Get()))
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