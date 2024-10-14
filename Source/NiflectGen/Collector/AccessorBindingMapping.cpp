#include "NiflectGen/Collector/AccessorBindingMapping.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/TaggedType/TaggedType.h"

namespace NiflectGen
{
	void CAccessorBindingMapping2::IterateForTemplate(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplateTypesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent, uint32& detailIteratingIdx) const
	{
		//auto argsCount = clang_Type_getNumTemplateArguments(fieldOrArgCXType);
		//for (int32 idx1 = 0; idx1 < argsCount; ++idx1)
		//{
		//	CXType argType = clang_Type_getTemplateArgumentAsType(fieldOrArgCXType, idx1);
		//	CBindingAccessorIndexedNode indexedChild;
		//	this->FindBindingTypeRecurs(argType, vecDetailCursor, resolvedTaggedTypeMapping, indexedChild, detailIteratingIdx);
		//	resultIndexedParent.m_vecChild.push_back(indexedChild);
		//}

		auto argsCount = clang_Type_getNumTemplateArguments(fieldOrArgCXType);
		ASSERT(!resultIndexedParent.m_isTemplateFormat);
		resultIndexedParent.m_isTemplateFormat = argsCount > 0;
		for (int32 idx1 = 0; idx1 < argsCount; ++idx1)
		{
			CXType argType = clang_Type_getTemplateArgumentAsType(fieldOrArgCXType, idx1);
			CResolvedCursorNode* indexedNext = NULL;
			if (argsCount > 1)
			{
				resultIndexedParent.m_vecChild.push_back(CResolvedCursorNode());
				indexedNext = &resultIndexedParent.m_vecChild.back();
			}
			else
			{
				//现无其它方式区分是否为结构模板, 当结构模板的模板参数确实为1个时, 流程错误
				//如认为有必要支持1个模板参数的结构模板, 应使用一种区分方式, 如通过在 UntaggedType 表中查找是否定义相应模板类, 且模板参数数量相同, 则可认定为结构模板
				//1维结构模板如
				//AccessorBindingSetting
				//template <typename T0>
				//NIF_BS() TBindingSetting<CCompoundAccessor, TestAccessor2::TMyTransform<T0> >;
				//成员
				//NIF_F()
				//TestAccessor2::TMyTransform<bool> m_tm_18;
				//可通过如下方式查找
				//auto c = clang_getTypeDeclaration(fieldOrArgCXType);
				//auto d = clang_getSpecializedCursorTemplate(c);
				//auto itFound = untaggedTemplateMapping.m_mapCursorToIndex.find(d);
				//if (itFound != untaggedTemplateMapping.m_mapCursorToIndex.end())
				//{
				//	//进一步检查模板参数对应的成员数量是否与模板参数相同, 是则为正确指定的结构模板, 否则为错误的容器模板
				//	printf("");
				//}
				//但仅通过某些结构特点认定, 是无法保证正确区分容器模板或结构模板, 因为类的用途是无法通过结构定义推断的
				//因此建议考虑限制框架功能
				//1. 当BindingType是1维模板, 则一定被认定为容器模板
				//2. 当BindingType是多维模板, 则一定将最后维的BindingType认定为结构模板, 其余为容器模板
				//另见 Main.cpp 中 12, 13 与 14 说明

				resultIndexedParent.m_elem = Niflect::MakeShared<CResolvedCursorNode>();
				indexedNext = resultIndexedParent.m_elem.Get();
			}
			this->FindBindingTypeRecurs(argType, vecDetailCursor, taggedMapping, untaggedTemplateMapping, *indexedNext, detailIteratingIdx);
		}
	}
	bool CAccessorBindingMapping2::FindBindingTypesSSSSSSSSSSS(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, uint32& detailIteratingIdx, CFoundResult& result) const
	{
		auto& foundIdx = result.m_foundIdx;
		auto& continuing = result.m_continuing;
		auto& indexedParent = result.m_indexedParent;
		Niflect::CString header;
		{
			auto itFound = m_mapCXTypeToIndex.find(fieldOrArgCXType);
			if (itFound != m_mapCXTypeToIndex.end())
				foundIdx = itFound->second;
		}
		if (foundIdx == INDEX_NONE)
		{
			//特化, <Niflect::TArrayNif<bool>, 可直接通过field本身CXType的cursor查找到BindingType的cursor
			auto cursor = clang_getTypeDeclaration(fieldOrArgCXType);
			auto itFound = m_mapSpecializedCursorToIndex.find(cursor);
			if (itFound != m_mapSpecializedCursorToIndex.end())
			{
				foundIdx = itFound->second;
				header = GetCursorFilePath(cursor);
				continuing = false;
			}
		}
		if (foundIdx == INDEX_NONE)
		{
			const CXCursor* refCursor = NULL;
			while (detailIteratingIdx < vecDetailCursor.size())
			{
				auto& it = vecDetailCursor[detailIteratingIdx];
				detailIteratingIdx++;
				auto kind = clang_getCursorKind(it);
				//查找首个可处理的类型的Ref
				if (kind == CXCursor_TemplateRef || kind == CXCursor_TypeRef)
				{
					refCursor = &it;
					break;
				}
			}
			if (refCursor != NULL)
			{
				auto cursor = clang_getCursorReferenced(*refCursor);
				auto itFound = m_mapCursorToIndex.find(cursor);
				if (itFound != m_mapCursorToIndex.end())
				{
					foundIdx = itFound->second;
					header = GetCursorFilePath(cursor);
					continuing = IsCursorTemplateDecl(cursor);
				}
			}
		}
		if (foundIdx != INDEX_NONE)
		{
			indexedParent.InitForAccessorBinding(foundIdx, header);
			return true;
		}
		return false;
	}
	void CAccessorBindingMapping2::FindBindingTypeRecurs(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplateTypesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent, uint32& detailIteratingIdx) const
	{
		CFoundResult result(resultIndexedParent);
		if (this->FindBindingTypesSSSSSSSSSSS(fieldOrArgCXType, vecDetailCursor, detailIteratingIdx, result))
		{
			resultIndexedParent.InitForTemplateBegin(m_vecAccessorBindingSetting[result.m_foundIdx].m_bindingTypeCursorName, result.m_foundIdx);

			if (result.m_continuing)
			{
				//auto& bindingSetting = m_vecAccessorBindingSetting[result.m_foundIdx];
				////模板套特化的 BindingType, 成员类型如 Niflect::TArrayNif<Niflect::TArrayNif<bool> >
				//this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, resolvedTaggedTypeMapping, resultIndexedParent, detailIteratingIdx);
				//resultIndexedParent.InitForTemplateArguments(resultIndexedParent);

				//auto elemDeclsCount = bindingSetting.GetELementBindingTypeDeclsCount();
				//if (elemDeclsCount > 0)
				//{
				//	auto pIndexedParent = &resultIndexedParent;
				//	//多维 BindingType, 如典型的 TStlMapAccessor 设置, 第0维为 TMap, 第1维为 sd::pair
				//	for (uint32 idx0 = 0; idx0 < elemDeclsCount; ++idx0)
				//	{
				//		auto& elemSubcursor = bindingSetting.GetELementBindingTypeDecl(idx0);
				//		pIndexedParent->m_next = Niflect::MakeShared<CBindingAccessorIndexedNode>();
				//		pIndexedParent = pIndexedParent->m_next.Get();
				//		CFoundResult result2222(*pIndexedParent);
				//		uint32 aaaa = 0;
				//		if (!this->FindBindingTypesSSSSSSSSSSS(elemSubcursor.m_CXType, elemSubcursor.m_vecAaaaaaaaaa, aaaa, result2222))
				//		{
				//			ASSERT(false);//todo: 报错, 每维BindingType都需要指定AccessorType
				//			break;
				//		}
				//		pIndexedParent->InitForTemplate(m_vecAccessorBindingSetting[result2222.m_foundIdx].m_bindingTypePattern, result2222.m_foundIdx, resultIndexedParent);
				//	}
				//}


				auto& bindingSetting = m_vecAccessorBindingSetting[result.m_foundIdx];

				auto elemDeclsCount = bindingSetting.GetELementBindingTypeDeclsCount();
				if (elemDeclsCount > 0)
				{
					auto pIndexedParent = &resultIndexedParent;
					//多维 BindingType, 如典型的 TStlMapAccessor 设置, 第0维为 TMap, 第1维为 sd::pair
					Niflect::TArrayNif<std::pair<CResolvedCursorNode*, uint32> > vecSSSSSSSSS;
					for (uint32 idx0 = 0; idx0 < elemDeclsCount; ++idx0)
					{
						auto& elemSubcursor = bindingSetting.GetELementBindingTypeDecl(idx0);
						pIndexedParent->m_elem = Niflect::MakeShared<CResolvedCursorNode>();
						pIndexedParent = pIndexedParent->m_elem.Get();
						CFoundResult result2222(*pIndexedParent);
						uint32 aaaa = 0;
						if (!this->FindBindingTypesSSSSSSSSSSS(elemSubcursor.m_CXType, elemSubcursor.m_vecAaaaaaaaaa, aaaa, result2222))
						{
							ASSERT(false);//todo: 报错, 每维BindingType都需要指定AccessorType
							break;
						}
						//pIndexedParent->InitForTemplate(m_vecAccessorBindingSetting[result2222.m_foundIdx].m_bindingTypePattern, result2222.m_foundIdx, resultIndexedParent);
						vecSSSSSSSSS.push_back({ pIndexedParent, result2222.m_foundIdx });
					}
					this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, taggedMapping, untaggedTemplateMapping, *pIndexedParent, detailIteratingIdx);
					resultIndexedParent.InitForTemplateArguments(*pIndexedParent);

					for (auto& it : vecSSSSSSSSS)
					{
						auto& foundIdx = it.second;
						it.first->InitForTemplate(m_vecAccessorBindingSetting[foundIdx].m_bindingTypeCursorName, foundIdx, *pIndexedParent);
					}
				}
				else
				{
					//模板套特化的 BindingType, 成员类型如 Niflect::TArrayNif<Niflect::TArrayNif<bool> >
					this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, taggedMapping, untaggedTemplateMapping, resultIndexedParent, detailIteratingIdx);
					resultIndexedParent.InitForTemplateArguments(resultIndexedParent);
				}
			}
			resultIndexedParent.InitForTemplateEnd();
		}
		else
		{
			auto cursor = clang_getTypeDeclaration(fieldOrArgCXType);
			taggedMapping.InitIndexedNodeForClassDecl(cursor, *this, resultIndexedParent);
		}
	}
	void CAccessorBindingMapping2::InitIndexedNodeForField(const CXCursor& fieldCursor, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplateTypesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent) const
	{
		auto fieldCXType = clang_getCursorType(fieldCursor);
		uint32 detailIteratingIdx = 0;
		this->FindBindingTypeRecurs(fieldCXType, vecDetailCursor, taggedMapping, untaggedTemplateMapping, resultIndexedParent, detailIteratingIdx);
	}
	static Niflect::CString GenerateBindingTypeCursorName(const CXCursor& cursor, const CXType& type)
	{
		Niflect::CString name;
		auto kind = clang_getCursorKind(cursor);
		if ((kind != CXCursor_NoDeclFound) && (kind != CXCursor_ClassDecl))
		{
			name = GenerateNamespacesAndScopesCode(cursor);
			name += CXStringToCString(clang_getCursorSpelling(cursor));
		}
		else
		{
			name = CXStringToCString(clang_getTypeSpelling(type));
		}
		return name;
	}

	enum class EMyVisitingState
	{
		None,
		Stop,
	};
	static void GenerateTemplateInstanceCodeRecurs3(const CSubcursor& parentSubcursor, EMyVisitingState& visitingState, Niflect::CString& text)
	{
		//该函数与旧实验 GenerateTemplateInstanceCode 流程类似, 主要区别为
		//1. 仅支持生成 FullScope 的名称
		//2. 根据 NiflectGenDefinition::CodeStyle 确定嵌套模板右尖括号是否加空格
		//3. 对于模板类型定义, 即非特化或非部分特化的 Subcursor, 不递归尖括号对应的 CXType, 仅生成名称, 即 CursorName
		Niflect::CString name;
		if (parentSubcursor.m_vecAaaaaaaaaa.size() > 0)
		{
			for (uint32 idx = 0; idx < parentSubcursor.m_vecAaaaaaaaaa.size(); ++idx)
			{
				auto& it = parentSubcursor.m_vecAaaaaaaaaa[idx];
				auto kind = clang_getCursorKind(it);
				{
					//手工编写对应的Cursor(如Field, AccessorBinding)不能保证scope(namespace与类scope)是完整的, 因此忽略, 通过GenerateNamespacesAndScopesCode生成完整scope
					if (kind != CXCursor_NamespaceRef)
					{
						if (clang_isReference(kind))
						{
							auto decl = clang_getCursorReferenced(it);

							bool isArgName = clang_getCursorKind(decl) == CXCursor_TemplateTypeParameter;
							if (!isArgName)
							{
								auto strScope = GenerateNamespacesAndScopesCode(decl);
								name += strScope;
							}
							else
							{
								visitingState = EMyVisitingState::Stop;
								return;
							}
							auto spelling = CXStringToCString(clang_getCursorSpelling(decl));
							name += spelling;

							if (idx != parentSubcursor.m_vecAaaaaaaaaa.size() - 1)
								name += "::";
						}
						else
						{
							ASSERT(false);
						}
					}
				}
			}
		}
		else
		{
			auto strScope = GenerateNamespacesAndScopesCode(parentSubcursor.m_cursorDecl);
			name += strScope;
			name += GetNameFromCursorOrTypeDeclaration(parentSubcursor.m_cursorDecl, parentSubcursor.m_CXType);
		}

		text += name;
		bool canRecurs = true;
		if (parentSubcursor.m_vecAaaaaaaaaa.size() > 0)
		{
			//m_vecChild为模板参数所引用的decl, 如TypedefAliasDecl, m_vecAaaaaaaaaa.back()中为模板参数的Spelling类型, 非模板为TypeRef, 模板为TemplateRef, 因此TypeRef不应继续递归
			if (clang_getCursorKind(parentSubcursor.m_vecAaaaaaaaaa.back()) == CXCursor_TypeRef)
			{
				canRecurs = false;
			}
		}
		else
		{
			canRecurs = clang_getCursorKind(parentSubcursor.m_cursorDecl) != CXCursor_TypeAliasDecl;
		}
		if ((canRecurs) && (parentSubcursor.m_vecChild.size() > 0))
		{
			Niflect::CString childrenText;
			for (uint32 idx = 0; idx < parentSubcursor.m_vecChild.size(); ++idx)
			{
				Niflect::CString childText;
				GenerateTemplateInstanceCodeRecurs3(parentSubcursor.m_vecChild[idx], visitingState, childText);

				if (visitingState == EMyVisitingState::Stop)
					break;

				childrenText += childText;
				if (idx != parentSubcursor.m_vecChild.size() - 1)
					childrenText += ", ";
			}
			if (!childrenText.empty())
			{
				NiflectGenDefinition::CodeStyle::TemplateAngleBracketL(text);
				text += childrenText;
				NiflectGenDefinition::CodeStyle::TemplateAngleBracketR(text);
			}
		}
	}
	void GenerateTemplateInstanceCode3(const CSubcursor& parentSubcursor, Niflect::CString& text)
	{
		auto visitingState = EMyVisitingState::None;
		GenerateTemplateInstanceCodeRecurs3(parentSubcursor, visitingState, text);
	}
	void CAccessorBindingMapping2::InitPatterns()
	{
		for (auto& it : m_vecAccessorBindingSetting)
		{
			//auto& aSubcursor = it.GetAccessorTypeDecl();
			//it.m_accessorTypePattern = GenerateNamespacesAndScopesCode(aSubcursor.m_cursorDecl);
			//it.m_accessorTypePattern += CXStringToCString(clang_getCursorSpelling(aSubcursor.m_cursorDecl));

			//auto& bSubcursor = it.GetBindingTypeDecl();
			//it.m_bindingTypePattern = GenerateBindingTypeCursorName(bSubcursor.m_cursorDecl, bSubcursor.m_CXType);

			GenerateTemplateInstanceCode3(it.GetAccessorTypeDecl(), it.m_accessorTypeCursorName);
			GenerateTemplateInstanceCode3(it.GetBindingTypeDecl(), it.m_bindingTypeCursorName);
		}
	}
}