#include "NiflectGen/Collector/AccessorBindingMapping.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/TaggedType/TaggedType.h"

namespace NiflectGen
{
	bool CAccessorBindingMapping2::IterateForTemplate(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplatesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent, uint32& detailIteratingIdx) const
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
		bool isTemplateFormat = argsCount > 0;
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
		return isTemplateFormat;
	}
	bool CAccessorBindingMapping2::InitResocursorNodeIfFound(CAccessorBindingFindingContext& ctx, CResolvedCursorNode& resocursorNode) const
	{
		uint32 foundAccessorBindingIdx = INDEX_NONE;
		uint32 foundUntaggedTemplateIndex = INDEX_NONE;
		auto& outDetailIteratingIdx = ctx.m_outDetailIteratingIdx;
		auto& continuing = ctx.m_continuing;

		Niflect::CString header;
		{
			auto itFound = m_mapCXTypeToIndex.find(ctx.m_fieldOrArgCXType);
			if (itFound != m_mapCXTypeToIndex.end())
				foundAccessorBindingIdx = itFound->second;
		}
		if (foundAccessorBindingIdx == INDEX_NONE)
		{
			//特化, <Niflect::TArrayNif<bool>, 可直接通过field本身CXType的cursor查找到BindingType的cursor
			auto cursor = clang_getTypeDeclaration(ctx.m_fieldOrArgCXType);
			auto itFound = m_mapSpecializedCursorToIndex.find(cursor);
			if (itFound != m_mapSpecializedCursorToIndex.end())
			{
				foundAccessorBindingIdx = itFound->second;
				header = GetCursorFilePath(cursor);
				continuing = false;
			}
		}
		if (foundAccessorBindingIdx == INDEX_NONE)
		{
			const CXCursor* refCursor = NULL;
			while (ctx.m_outDetailIteratingIdx < ctx.m_vecDetailCursor.size())
			{
				auto& it = ctx.m_vecDetailCursor[outDetailIteratingIdx];
				outDetailIteratingIdx++;
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
					foundAccessorBindingIdx = itFound->second;
					header = GetCursorFilePath(cursor);
					bool isTemplate = IsCursorTemplateDecl(cursor);
					if (isTemplate)
					{
						auto itFound = ctx.m_untaggedTemplateMapping.m_mapCursorToIndex.find(cursor);
						ASSERT(itFound != ctx.m_untaggedTemplateMapping.m_mapCursorToIndex.end());
						foundUntaggedTemplateIndex = itFound->second;
					}
					continuing = isTemplate;
				}
			}
		}
		if (foundAccessorBindingIdx != INDEX_NONE)
		{
			resocursorNode.InitForAccessorBinding(foundAccessorBindingIdx, foundUntaggedTemplateIndex, header);
			return true;
		}
		return false;
	}
	void CAccessorBindingMapping2::FindBindingTypeRecurs(const CXType& fieldOrArgCXType, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplatesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent, uint32& detailIteratingIdx) const
	{
		CAccessorBindingFindingContext result(fieldOrArgCXType, vecDetailCursor, untaggedTemplateMapping, detailIteratingIdx);
		if (this->InitResocursorNodeIfFound(result, resultIndexedParent))
		{
			auto& bindingSetting = m_settings.m_vecAccessorBindingSetting[resultIndexedParent.m_accessorBindingIndex];
			resultIndexedParent.InitForTemplateBegin(bindingSetting.m_bindingTypeCursorName);

			if (result.m_continuing)
			{
				auto elemDeclsCount = bindingSetting.GetELementBindingTypeDeclsCount();
				if (elemDeclsCount > 0)
				{
					auto pIndexedParent = &resultIndexedParent;
					//1维容器模板套多参数结构模板的 BindingType, 如典型的 TStlMapAccessor 设置, 1维容器模板为 TMap, 多参数结构模板 sd::pair, 另见 ContainerTemplate1D 与 StructuralTemplateND 的概念说明
					Niflect::TArrayNif<CResolvedCursorNode*> vecElemResocursorNode;
					for (uint32 idx0 = 0; idx0 < elemDeclsCount; ++idx0)
					{
						auto& elemSubcursor = bindingSetting.GetELementBindingTypeDecl(idx0);
						pIndexedParent->m_elem = Niflect::MakeShared<CResolvedCursorNode>();
						pIndexedParent = pIndexedParent->m_elem.Get();
						uint32 aaaa = 0;
						CAccessorBindingFindingContext result2222(elemSubcursor.m_CXType, elemSubcursor.m_vecAaaaaaaaaa, untaggedTemplateMapping, aaaa);
						if (!this->InitResocursorNodeIfFound(result2222, *pIndexedParent))
						{
							ASSERT(false);//todo: 报错, 每维BindingType都需要指定AccessorType
							break;
						}
						vecElemResocursorNode.push_back(pIndexedParent);
					}
					bool isTemplateFormat = this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, taggedMapping, untaggedTemplateMapping, *pIndexedParent, detailIteratingIdx);
					resultIndexedParent.InitForTemplateArguments(*pIndexedParent, isTemplateFormat);

					for (auto& it : vecElemResocursorNode)
					{
						auto& elemSetting = m_settings.m_vecAccessorBindingSetting[it->m_accessorBindingIndex];
						it->InitForTemplate(elemSetting.m_bindingTypeCursorName, *pIndexedParent, isTemplateFormat);
					}
				}
				else
				{
					//模板套特化的 BindingType, 成员类型如 Niflect::TArrayNif<Niflect::TArrayNif<bool> >
					bool isTemplateFormat = this->IterateForTemplate(fieldOrArgCXType, vecDetailCursor, taggedMapping, untaggedTemplateMapping, resultIndexedParent, detailIteratingIdx);
					resultIndexedParent.InitForTemplateArguments(resultIndexedParent, isTemplateFormat);
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
	void CAccessorBindingMapping2::InitIndexedNodeForField(const CXCursor& fieldCursor, const Niflect::TArrayNif<CXCursor>& vecDetailCursor, const CTaggedTypesMapping& taggedMapping, const CUntaggedTemplatesMapping& untaggedTemplateMapping, CResolvedCursorNode& resultIndexedParent) const
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

	enum class EGenerateAccessorBindingCursorNameVisitingState
	{
		None,
		Stop,
	};
	static void GenerateAccessorBindingCursorNameRecurs(const CSubcursor& parentSubcursor, EGenerateAccessorBindingCursorNameVisitingState& visitingState, Niflect::CString& text)
	{
		//该函数与旧实验 GenerateTemplateInstanceCode 流程类似, 主要区别为
		//1. 仅支持生成 FullScope 的名称
		//2. 根据 NiflectGenDefinition::CodeStyle 确定嵌套模板右尖括号是否加空格
		//3. 对于模板类型定义, 即非特化或非部分特化的 Subcursor, 不递归尖括号对应的 CXType, 仅生成名称, 即 CursorName
		//不复用 FindBindingTypeRecurs 的原因是 AccessorBinding 中出现的类型, 不一定都是 Collect 阶段支持收集的类型, 如各种 Accessor 子类, 通常是无标记的
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
								visitingState = EGenerateAccessorBindingCursorNameVisitingState::Stop;
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
				GenerateAccessorBindingCursorNameRecurs(parentSubcursor.m_vecChild[idx], visitingState, childText);

				if (visitingState == EGenerateAccessorBindingCursorNameVisitingState::Stop)
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
	void GenerateAccessorBindingCursorName(const CSubcursor& parentSubcursor, Niflect::CString& text)
	{
		auto visitingState = EGenerateAccessorBindingCursorNameVisitingState::None;
		GenerateAccessorBindingCursorNameRecurs(parentSubcursor, visitingState, text);
	}
	void CAccessorBindingMapping2::InitPatterns()
	{
		for (auto& it : m_settings.m_vecAccessorBindingSetting)
		{
			//auto& aSubcursor = it.GetAccessorTypeDecl();
			//it.m_accessorTypePattern = GenerateNamespacesAndScopesCode(aSubcursor.m_cursorDecl);
			//it.m_accessorTypePattern += CXStringToCString(clang_getCursorSpelling(aSubcursor.m_cursorDecl));

			//auto& bSubcursor = it.GetBindingTypeDecl();
			//it.m_bindingTypePattern = GenerateBindingTypeCursorName(bSubcursor.m_cursorDecl, bSubcursor.m_CXType);

			GenerateAccessorBindingCursorName(it.GetAccessorTypeDecl(), it.m_accessorTypeCursorName);
			GenerateAccessorBindingCursorName(it.GetBindingTypeDecl(), it.m_bindingTypeCursorName);
		}
		if (m_settings.m_settingCompound.IsValid())
			GenerateAccessorBindingCursorName(m_settings.m_settingCompound.GetAccessorTypeDecl(), m_settings.m_settingCompound.m_accessorTypeCursorName);
		if (m_settings.m_settingEnumClass.IsValid())
			GenerateAccessorBindingCursorName(m_settings.m_settingEnumClass.GetAccessorTypeDecl(), m_settings.m_settingEnumClass.m_accessorTypeCursorName);
		if (m_settings.m_settingEnumBitMask.IsValid())
			GenerateAccessorBindingCursorName(m_settings.m_settingEnumBitMask.GetAccessorTypeDecl(), m_settings.m_settingEnumBitMask.m_accessorTypeCursorName);
	}
}