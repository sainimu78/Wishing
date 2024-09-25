#include "NiflectGen/Collector/Collector.h"
#include "Niflect/Util/StringUtil.h"
#include "NiflectGen/Log/Log.h"
#include "Niflect/Util/DebugUtil.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "NiflectGen/TaggedType/TaggedStruct.h"
#include "NiflectGen/TaggedType/TaggedClass.h"
#include "NiflectGen/TaggedType/TaggedEnum.h"

#include "NiflectGen/Collector/TemplateSubcursor.h"//备用, 现已另作实现, 见CSubcursor

//名词说明
//CodeTag: 指NiflectGen专用的标记, 如NiflectGenDefinition::CodeTag中的定义, 对应NiflectMacro.h中的如typedef void* __NiflectGen_Type标识
//Macro或MacroExpansion: 指NiflectMacro.h中如NIF_T宏, 展开内容即为Tag, 这样设计的好处在于用户可自定义NIF_T反射宏的名称
//TaggedNode: 指被CodeTag标记为被反射的类型定义, 现支持3种, class, struct, enum
//Subcursor: 概念与Cursor类似, 用于Cursor所不支持的一些数据以的树形结构表示, 现用于BindingSetting模板类实例的树形表示

namespace NiflectGen
{
	using namespace Niflect;

	using CCursorArray = Niflect::TArrayNif<CXCursor>;

	static bool CXType_IsBuiltinType(CXTypeKind typeKind)
	{
		return (typeKind > CXType_FirstBuiltin && typeKind < CXType_LastBuiltin);
	}
	static void CollectTemplateSubcursorRecurs(const CXType& parentType, const CCursorArray& vecCursor, CTemplateSubcursor& parentSubcursor, int& cursorArrayFrontIndex)
	{
		parentSubcursor.m_type = parentType;
		auto templateArgsCount = clang_Type_getNumTemplateArguments(parentType);
		auto originalType = GetPointerOriginalType(parentType);
		if (!CXType_IsBuiltinType(originalType.kind))
		{
			ASSERT(cursorArrayFrontIndex < vecCursor.size());
			parentSubcursor.m_cursor = vecCursor[cursorArrayFrontIndex];
			cursorArrayFrontIndex++;
		}
		for (int idx = 0; idx < templateArgsCount; ++idx)
		{
			CXType argType = clang_Type_getTemplateArgumentAsType(parentType, idx);
			parentSubcursor.m_vecChild.push_back(CTemplateSubcursor());
			auto& childSubcursor = parentSubcursor.m_vecChild.back();
			CollectTemplateSubcursorRecurs(argType, vecCursor, childSubcursor, cursorArrayFrontIndex);
		}
	}
	//static void CollectTemplateSubcursorRecurs2(const CXType& parentType, const CCursorArray& vecCursor, CTemplateSubcursor& parentSubcursor, int& cursorArrayFrontIndex)
	//{
	//	auto templateArgsCount = clang_Type_getNumTemplateArguments(parentType);
	//	auto& cursor = vecCursor[cursorArrayFrontIndex];

	//	auto sssss = CXStringToCString(clang_getCursorSpelling(cursor));
	//	auto ddddd = CXStringToCString(clang_getTypeSpelling(parentType));

	//	auto cursorKind = clang_getCursorKind(cursor);
	//	if (cursorKind == CXCursor_TemplateRef)
	//	{
	//		parentSubcursor.m_cursor = cursor;
	//		parentSubcursor.m_type = parentType;
	//		if (templateArgsCount > 0)
	//		{
	//			parentSubcursor.m_vecChild.resize(templateArgsCount);
	//			cursorArrayFrontIndex++;
	//		}
	//	}
	//	else
	//	{
	//		if (cursorKind == CXCursor_NamespaceRef)
	//		{
	//			parentSubcursor.m_vecScopeCursor.push_back(cursor);
	//			parentSubcursor.m_vecScopeType.push_back(CXType{ CXType_Invalid });
	//			cursorArrayFrontIndex++;
	//			CollectTemplateSubcursorRecurs2(parentType, vecCursor, parentSubcursor, cursorArrayFrontIndex);
	//		}
	//		else if (cursorKind == CXCursor_TypeRef)
	//		{
	//			parentSubcursor.m_cursor = cursor;
	//			parentSubcursor.m_type = parentType;
	//			cursorArrayFrontIndex++;
	//		}
	//		else
	//		{
	//			parentSubcursor.m_type = parentType;
	//		}
	//		//auto originalType = GetPointerOriginalType(parentType);
	//		//if (!CXType_IsBuiltinType(originalType.kind))
	//		//{

	//		//}
	//	}

	//	for (int idx = 0; idx < templateArgsCount; ++idx)
	//	{
	//		auto argType = clang_Type_getTemplateArgumentAsType(parentType, idx);
	//		CollectTemplateSubcursorRecurs2(argType, vecCursor, parentSubcursor.m_vecChild[idx], cursorArrayFrontIndex);
	//	}
	//}
	 


	//static void CollectTemplateSubcursorRecurs2(const CXType& parentType, const CCursorArray& vecCursor, CTemplateSubcursor& parentSubcursor, int& cursorArrayFrontIndex)
	//{
	//	//auto templateArgsCount = clang_Type_getNumTemplateArguments(parentType);
	//	//auto& cursor = vecCursor[cursorArrayFrontIndex];
	//	////auto sssss = CXStringToCString(clang_getCursorSpelling(cursor));
	//	//auto ddddd = CXStringToCString(clang_getTypeSpelling(parentType));
	//	//printf("%s, %d\n", ddddd.c_str(), templateArgsCount);
	//	//printf("");

	//	//for (int idx = 0; idx < templateArgsCount; ++idx)
	//	//{
	//	//	auto argType = clang_Type_getTemplateArgumentAsType(parentType, idx);
	//	//	CollectTemplateSubcursorRecurs2(argType, vecCursor, parentSubcursor, cursorArrayFrontIndex);
	//	//}

	//	for (int idx = 0; idx < vecCursor.size(); ++idx)
	//	{
	//		auto& cursor = vecCursor[idx];
	//		auto type = clang_getCursorType(cursor);
	//		auto templateArgsCount = clang_Type_getNumTemplateArguments(type);
	//		auto sssss = CXStringToCString(clang_getCursorSpelling(cursor));
	//		//auto ddddd = CXStringToCString(clang_getTypeSpelling(parentType));
	//		printf("%s, %d\n", sssss.c_str(), templateArgsCount);
	//		printf("");
	//	}
	//}

	static void CollectTemplateSubcursorRecurs_______(const CCursorArray& vecCursor, int& cursorArrayFrontIndex)
	{
		while (true)
		{
			auto& cursor = vecCursor[cursorArrayFrontIndex];

			CXType typeInTemplateScope = clang_getCursorType(cursor);
			int numTemplateArgs = clang_Type_getNumTemplateArguments(typeInTemplateScope);
			//auto kind = clang_getCursorKind(cursor);
			//if (kind == CXCursor_TypeRef)
			//{
			//	auto typeRef = clang_getCursorType(cursor);
			//	auto decl = clang_getTypeDeclaration(typeRef);
			//	auto a = CXStringToCString(clang_getCursorSpelling(decl));
			//	auto b = CXStringToCString(clang_getCursorSpelling(endCursor));
			//	if (clang_equalCursors(decl, endCursor))
			//		break;
			//}
			cursorArrayFrontIndex++;
		}
	}

	static void CollectTemplateSubcursorRecurs2(const CXType& parentType, const CCursorArray& vecCursor, CTemplateSubcursor& parentSubcursor, int& cursorArrayFrontIndex)
	{
		auto templateArgsCount = clang_Type_getNumTemplateArguments(parentType);
		auto& cursor = vecCursor[cursorArrayFrontIndex];

		parentSubcursor.m_type = parentType;
		parentSubcursor.m_cursor = clang_getTypeDeclaration(parentType);
		if (templateArgsCount > 0)
			parentSubcursor.m_vecChild.resize(templateArgsCount);

		////if (parentType.kind == CXType_Typedef)
		//if (clang_getCursorKind(parentSubcursor.m_cursor) == CXCursor_TemplateRef)
		//	CollectTemplateSubcursorRecurs_______(vecCursor, parentSubcursor.m_cursor, cursorArrayFrontIndex);
		
		//parentSubcursor.m_ccccccRoot.m_vecChild.push_back(CCCCCCCCCCC());
		//parentSubcursor.m_ccccccRoot.m_vecChild.back().m_cursor = vecCursor[cursorArrayFrontIndex];
		//cursorArrayFrontIndex++;
		
		//CollectTemplateSubcursorRecurs_______(vecCursor, cursorArrayFrontIndex);

		for (int idx = 0; idx < templateArgsCount; ++idx)
		{
			auto argType = clang_Type_getTemplateArgumentAsType(parentType, idx);
			auto& child = parentSubcursor.m_vecChild[idx];
			CollectTemplateSubcursorRecurs2(argType, vecCursor, child, cursorArrayFrontIndex);
			//CollectTemplateSubcursorRecurs_______(vecCursor, parentSubcursor.m_ccccccRoot.m_vecChild.back(), parentSubcursor.m_cursor, cursorArrayFrontIndex);
		}
	}


	static void FindNamespaceCursorNameRecurs(const CXCursor& cursor, CString& strNamespace)
	{
		CXCursor parentCursor;
		if (clang_getCursorKind(cursor) == CXCursor_TemplateRef)
		{
			parentCursor = clang_getCursorReferenced(cursor);
			FindNamespaceCursorNameRecurs(parentCursor, strNamespace);
		}
		else
		{
			parentCursor = clang_getCursorSemanticParent(cursor);
		}

		if (clang_getCursorKind(parentCursor) == CXCursor_Namespace)
		{
			FindNamespaceCursorNameRecurs(parentCursor, strNamespace);

			CXString namespaceName = clang_getCursorSpelling(parentCursor);
			strNamespace = CString(clang_getCString(namespaceName));
			clang_disposeString(namespaceName);
		}
		else if (clang_getCursorKind(parentCursor) == CXCursor_ClassDecl)
		{
			FindNamespaceCursorNameRecurs(parentCursor, strNamespace);
		}
		else if (clang_getCursorKind(parentCursor) == CXCursor_TranslationUnit)
		{
			strNamespace = "CustomInGlobal";
			return;
		}
	}
	static void PrintTemplateSubcursor(const CTemplateSubcursor& parentSubcursor, int level)
	{
		CString displayName;
		auto originalType = parentSubcursor.m_type;
		while (originalType.kind == CXType_Pointer)
			originalType = clang_getPointeeType(originalType);
		CXCursor cursor = parentSubcursor.m_cursor;
		if (parentSubcursor.m_type.kind != CXType_Invalid)
			cursor = clang_getTypeDeclaration(originalType);
		if (parentSubcursor.m_type.kind == CXType_Pointer)
		{
			displayName = CXStringToCString(clang_getTypeSpelling(parentSubcursor.m_type));
		}
		else
		{
			if (clang_getCursorKind(cursor) != CXCursor_NoDeclFound)
				displayName = CXStringToCString(clang_getCursorSpelling(parentSubcursor.m_cursor));//如果以cursor获取则可看到using定义的类型别名
			else
				displayName = CXStringToCString(clang_getTypeSpelling(originalType));
		}

		CString strNamespace;
		{
			if (clang_getCursorKind(cursor) != CXCursor_NoDeclFound)
				FindNamespaceCursorNameRecurs(cursor, strNamespace);
			else
				strNamespace = "BuiltinInGlobal";
		}

		auto strLevel = NiflectUtil::DebugIndentToString(level);
		printf("%s%s, %s\n", strLevel.c_str(), displayName.c_str(), strNamespace.c_str());

		level++;
		for (auto& it : parentSubcursor.m_vecChild)
			PrintTemplateSubcursor(it, level);
	}

	void PrintTemplateSubcursor333333333(const CTemplateSubcursor& parentSubcursor, int level)
	{
		CString displayName;
		auto originalType = parentSubcursor.m_type;
		while (originalType.kind == CXType_Pointer)
			originalType = clang_getPointeeType(originalType);
		CXCursor cursor = parentSubcursor.m_cursor;
		if (parentSubcursor.m_type.kind != CXType_Invalid)
			cursor = clang_getTypeDeclaration(originalType);
		if (parentSubcursor.m_type.kind == CXType_Pointer)
		{
			displayName = CXStringToCString(clang_getTypeSpelling(parentSubcursor.m_type));
		}
		else
		{
			if (clang_getCursorKind(cursor) != CXCursor_NoDeclFound)
				displayName = CXStringToCString(clang_getCursorSpelling(parentSubcursor.m_cursor));//如果以cursor获取则可看到using定义的类型别名
			else
				displayName = CXStringToCString(clang_getTypeSpelling(originalType));
		}

		CString strNamespace;
		{
			if (clang_getCursorKind(cursor) != CXCursor_NoDeclFound)
				FindNamespaceCursorNameRecurs(cursor, strNamespace);
			else
				strNamespace = "BuiltinInGlobal";
		}

		auto strLevel = NiflectUtil::DebugIndentToString(level);
		printf("%s%s, %s\n", strLevel.c_str(), displayName.c_str(), strNamespace.c_str());

		level++;
		for (auto& it : parentSubcursor.m_vecChild)
			PrintTemplateSubcursor333333333(it, level);
	}

	class CScopeNamespace
	{
	public:
		CScopeNamespace(CDataCollector& collection, const CXCursor& cursor)
			: m_collection(collection)
			, m_entered(false)
		{
			if (clang_getCursorKind(cursor) == CXCursor_Namespace)
			{
				m_collection.m_stkNamespaceCursor.push_back(cursor);
				m_entered = true;
			}
		}
		~CScopeNamespace()
		{
			if (m_entered)
				m_collection.m_stkNamespaceCursor.pop_back();
		}

	private:
		CDataCollector& m_collection;
		bool m_entered;
	};

	class CScopeBindingSetting
	{
	public:
		CScopeBindingSetting(CDataCollector& collection, const CXCursor& cursor, const CCursorArray& vecChild, const CCollectingContext& context, SRecursCollectingData& recursCollectiingData)
			: m_collection(collection)
			, m_cursor(cursor)
			, m_vecChild(vecChild)
			, m_context(context)
			, m_recursCollectiingData(recursCollectiingData)
			, m_entered(false)
		{
			if (m_collection.GetNamespaceDepth() <= 1)//TypeBinding仅支持定义在全局或1层深的namespace中
			{
				m_entered = FindTagByKindAndDisplayName(m_cursor, CXCursor_TypeAliasDecl, NiflectGenDefinition::CodeTag::BindingSetting);
				
				//2024.09.23, TAccessorBinding的量不可能大, 另为可顺便支持任意符合语法的别名, 因此不限制必须在首个AccessorBinding之前定义好所有类型或别名
				//if (m_entered)
				//	m_collection.m_collectingClassBaseCursorDecl = false;//逻辑为遍历到BindingSetting配置头文件中的cursor之前一定已经遍历完所有Accessor类型
			}
		}
		~CScopeBindingSetting()
		{
			if (m_entered)
			{
				MyLogErrorChecked(m_vecChild.size() > 0, NiflectUtil::FormatString("Template must have child nodes"));
				MyLogErrorChecked(clang_getCursorKind(m_vecChild[0]) == CXCursor_TemplateRef, NiflectUtil::FormatString("The first node must be TemplateRef"));

				CXType templateType = clang_getCursorType(m_cursor);
				CBindingSettingData data;
				if (!BuildSubcursor(templateType, m_vecChild, data.m_subcursorRoot))
				{
					GenLogError(m_context.m_log, "Fail to apply the BindingSetting");
					return;
				}
				//auto a = CXStringToCString(clang_getTypeSpelling(templateType));
				////CollectTemplateSubcursorRecurs2(templateType, m_vecChild, data.m_subCursorRoot, cursorArrayFrontIndex);
				//auto& b = m_vecChild[5];
				//auto c = clang_isReference(b.kind);
				//auto d = clang_getCursorReferenced(b);

				//PrintSubcursorRecurs(data.m_subcursorRoot);
				//Niflect::CString str0;
				//GenerateTemplateInstanceCode(data.m_subcursorRoot.m_vecChild[0], str0);
				//Niflect::CString str1;
				//GenerateTemplateInstanceCode(data.m_subcursorRoot.m_vecChild[1], str1);
				m_recursCollectiingData.m_vecAccessorBindingSetting.push_back(data);
			}
		}

	private:
		CDataCollector& m_collection;
		const CXCursor& m_cursor;
		const CCursorArray& m_vecChild;
		const CCollectingContext& m_context;
		SRecursCollectingData& m_recursCollectiingData;
		bool m_entered;
	};

	static bool IsTypeForBaseClassVerifying(CXCursorKind kind)
	{
		return kind == CXCursor_ClassDecl || kind == CXCursor_ClassTemplate;
	}

	class CScopeAccessorBaseCursorDecl
	{
	public:
		CScopeAccessorBaseCursorDecl(CDataCollector& collection, const CXCursor& cursor, const CCursorArray& vecChild)
			: m_collection(collection)
			, m_cursor(cursor)
			, m_vecChild(vecChild)
			, m_entered(false)
		{
			m_entered = IsTypeForBaseClassVerifying(clang_getCursorKind(cursor));
		}
		~CScopeAccessorBaseCursorDecl()
		{
			if (m_entered)
			{
				CXCursor foundCursor = g_invalidCursor;
				for (uint32 idx = 0; idx < m_vecChild.size(); ++idx)
				{
					//似乎可遍历获取多继承定义, 但多继承的支持不在规划中
					if (clang_getCursorKind(m_vecChild[idx]) == CXCursor_CXXBaseSpecifier)
					{
						foundCursor = m_vecChild[idx];
						break;
					}
				}
				bool canAdd = !clang_Cursor_isNull(foundCursor);
				if (!canAdd)
					canAdd = IsCAccessorClassDecl(m_cursor);//现second用于表示链接的基类, 为避免记录太多无关cursor, 因此检查只保留特殊类的cursor
				if (canAdd)
				{
					auto ret = m_collection.m_mapCursorDeclToBaseCursorDecl.insert({ m_cursor, foundCursor });
					ASSERT(ret.second);
				}
			}
		}

	private:
		CDataCollector& m_collection;
		const CXCursor& m_cursor;
		const CCursorArray& m_vecChild;
		bool m_entered;
	};

	//todo: 应改为 ScopeAliasChainLinking ?
	class CScopeTemplateDecl
	{
	public:
		CScopeTemplateDecl(const CXCursor& cursor, const CCursorArray& vecChild, const CXCursor& parentCursor, CAliasChain* aliasChain)
			: m_cursor(cursor)
			, m_vecChild(vecChild)
			, m_parentCursor(parentCursor)
			, m_aliasChain(aliasChain)
			, m_entered(false)
		{
			m_entered = clang_getCursorKind(cursor) == CXCursor_TypeAliasDecl;
		}
		~CScopeTemplateDecl()
		{
			if (m_entered)
			{
				for (uint32 idx = 0; idx < m_vecChild.size(); ++idx)
				{
					auto& cursor = m_vecChild[idx];

					//auto a = CXStringToCString(clang_getCursorSpelling(m_parentCursor));
					//auto b = CXStringToCString(clang_getCursorSpelling(m_cursor));
					//printf("%s, %s\n", a.c_str(), b.c_str());

					//if (b == "MyString")
					//	printf("");

					auto childKind = clang_getCursorKind(cursor);
					if (childKind == CXCursor_TypeRef || childKind == CXCursor_TemplateRef)
					{
						auto dsssssssss = m_cursor;
						bool ok = false;
						if (clang_getCursorKind(m_parentCursor) == CXCursor_TypeAliasTemplateDecl)
						{
							ok = true;
							dsssssssss = m_parentCursor;
						}
						else if (clang_getCursorKind(m_cursor) == CXCursor_TypeAliasDecl)
						{
							ok = true;
						}
						if (ok)
						{
							m_aliasChain->LinkToReferenced(dsssssssss, cursor);
						}
						break;
					}
				}
			}
		}

	private:
		const CXCursor& m_cursor;
		const CXCursor& m_parentCursor;
		const CCursorArray& m_vecChild;
		CAliasChain* m_aliasChain;
		bool m_entered;
	};

	CVisitingDebugData::CVisitingDebugData()
		: m_allCursorsCountForChecking(0)
		, m_fp(NULL)
		, m_level(0)
		, m_allCursorsCount(0)
	{

	}
	void CVisitingDebugData::Init(const CXCursor& cursor, FILE* fp)
	{
		m_allCursorsCountForChecking = 0;
		m_fp = fp;
		m_level = 0;
		m_allCursorsCount = 0;

		CVisitCallbacks callbacks;
		callbacks.m_EnterFunc = [this](const CXCursor& cursor)
			{
				m_allCursorsCountForChecking++;
			};
		VisitCursorRecurs(cursor, callbacks);
	}
	bool CVisitingDebugData::Check() const
	{
		if (m_allCursorsCount != m_allCursorsCountForChecking)
		{
			ASSERT(false);
			return false;
		}
		return true;
	}

	CTaggedTypeCollector::CTaggedTypeCollector(CMacroTagCollection2& tagCollection)
		: m_tagCollection(tagCollection)
		, m_stage(EStage::None)
		, m_tagLocation{}
	{

	}
	bool CTaggedTypeCollector::Collect(const CXCursor& cursor, CTaggedNode2* taggedParent, CGenLog* log)
	{
		bool addedTaggedChidl = false;
		if (m_stage == EStage::None)
		{
			if (FindTagByKindAndDisplayName(cursor, CXCursor_TypedefDecl, NiflectGenDefinition::CodeTag::Type))
			{
				m_tagLocation = clang_getCursorLocation(cursor);
				m_stage = EStage::Found;
			}
		}
		else if (m_stage == EStage::Found)
		{
			TSharedPtr<CTaggedType> taggedChild;
			auto kind = clang_getCursorKind(cursor);
			if (kind == CXCursor_ClassDecl)
				taggedChild = MakeShared<CTaggedClass>();
			else if (kind == CXCursor_EnumDecl)
				taggedChild = MakeShared<CTaggedEnum>();
			else if (kind == CXCursor_StructDecl)
				taggedChild = MakeShared<CTaggedStruct>();
			if (taggedChild != NULL)
			{
				CXCursor macroCursor;
				m_tagCollection.TakeByTagLocation(m_tagLocation, macroCursor);
				taggedParent->AddChildAndInitDefault(taggedChild, cursor, macroCursor);
				m_stage = EStage::None;
				addedTaggedChidl = true;
			}
			else
			{
				GenLogError(log, "The type must be either a class, a struct, or an enum");
			}
		}
		return addedTaggedChidl;
	}

	CTemplateCollector::CTemplateCollector()
	{

	}
	bool CTemplateCollector::Collect(const CXCursor& cursor, CTaggedNode2* taggedParent, CGenLog* log)
	{
		//由于clang_visitChildren是深度优先遍历, 进入AccessorBinding设置头文件时, 先继续向引用的头文件递归, 因此不能提前确定需要记录实际用到的UntaggedTemplate, 如能控制遍历方式为广度优先, 则可提前确定实际使用的非1维BindingType的UntaggedTemplate
		taggedParent->AddChildAndInitDefault(MakeShared<CUntaggedTemplate>(), cursor, g_invalidCursor);
		return true;
	}

	CDataCollector::CDataCollector()
		: m_taggedTypeCollector(m_macroTagCollection)
		, m_collectingClassBaseCursorDecl(true)
	{
	}
	uint32 CDataCollector::GetNamespaceDepth() const
	{
		return static_cast<uint32>(m_stkNamespaceCursor.size());
	}
	const CXCursor& CDataCollector::GetVisitingNamespaceReserved() const
	{
		static CXCursor s_invalidCursor{};
		if (m_stkNamespaceCursor.size() > 0)
			return m_stkNamespaceCursor.back();
		return s_invalidCursor;
	}
	struct SVisitorCallbackData
	{
		CDataCollector* m_this;
		CTaggedNode2* m_taggedParent;
		CCollectingContext& m_context;
		CAliasChain* m_aliasChain;
		CCursorArray m_vecCursorChild;
		SVisitingData m_visitingData;
	};
	void CDataCollector::Visit(const CXCursor& cursor, CTaggedNode2* taggedParent, CCollectingContext& context, CAliasChain* aliasChain, SVisitingData& data)
	{
		uint32 taggedChildIndex = taggedParent->GetChildrenCount();
		bool addedTaggedChild = false;
		if (!m_macroTagCollection.CollectMacroExpansion(cursor))
		{
			if (m_collectingClassBaseCursorDecl)
			{
				auto kind = clang_getCursorKind(cursor);

				//if (IsTypeForBaseClassVerifying(kind))
				//{
				//	auto ret = m_mapCursorDeclToBaseCursorDecl.insert({ cursor, g_invalidCursor });
				//	ASSERT(ret.second);
				//}

				if (kind == CXCursor_TypeAliasTemplateDecl)
				{
					aliasChain->AddLinkDecl(cursor);
					addedTaggedChild = m_templateCollector.Collect(cursor, taggedParent, context.m_log);
				}
				else if (kind == CXCursor_TypeAliasDecl)
				{
					aliasChain->AddLinkDecl(cursor);
				}
				else if (kind == CXCursor_ClassTemplate)
				{
					aliasChain->AddLinkDecl(cursor);
					addedTaggedChild = m_templateCollector.Collect(cursor, taggedParent, context.m_log);
				}
			}
			if (!addedTaggedChild)
			{
				addedTaggedChild = m_taggedTypeCollector.Collect(cursor, taggedParent, context.m_log);
				if (!addedTaggedChild)
				{
					STaggedNodeCollectingContext taggedNodeContext{ m_macroTagCollection, context.m_log };
					addedTaggedChild = taggedParent->CollectSibling(cursor, taggedNodeContext);
				}
			}
		}
		if (addedTaggedChild)
			data.m_vecTaggedChildIndex.push_back(taggedChildIndex);
		else
			data.m_vecTaggedChildIndex.push_back(INDEX_NONE);
	}
	static CXChildVisitResult VisitorCallback(CXCursor cursor, CXCursor parent, CXClientData data)
	{
		auto& d = *static_cast<SVisitorCallbackData*>(data);
		d.m_this->Visit(cursor, d.m_taggedParent, d.m_context, d.m_aliasChain, d.m_visitingData);
		d.m_vecCursorChild.push_back(cursor);

		return CXChildVisit_Continue;
	}
	bool CDataCollector::VerifyDerivedFromCAccessor(CXCursor p, CAliasChain* aliasChain) const
	{
		//todo: 可考虑收集到树型结构中, 避免使用接口临时获取
		bool ok = false;
		while (true)
		{
			if (IsCAccessorClassDecl(p))
			{
				ok = true;
				break;
			}
			p = aliasChain->FindOriginalDecl(p);
			auto itFound = m_mapCursorDeclToBaseCursorDecl.find(p);
			if (itFound != m_mapCursorDeclToBaseCursorDecl.end())
			{
				if (!clang_Cursor_isNull(itFound->second))
				{
					p = clang_getTypeDeclaration(clang_getCursorType(itFound->second));
				}
				else
				{
					if (IsCAccessorClassDecl(p))
						ok = true;
					break;//second为基类cursor, 为空则表明不需要再继续, 因此break
				}
			}
			else
			{
				break;
			}
		}
		return ok;
	}
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
	CXCursor CAliasChain::FindOriginalDecl(CXCursor decl) const
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
	CXCursor CDataCollector::FindAliasDeclOld(CXCursor decl) const
	{
		ASSERT(false);
		return g_invalidCursor;
		//return m_aliasChain->FindOriginalDecl(decl);
	}
	void CDataCollector::Collect(const CXCursor& cursor, CTaggedNode2* taggedParent, CCollectingContext& context, CCollectionData& collectionData)
	{
		auto aliasChain = Niflect::MakeShared<CAliasChain>();
		auto accessorBindingMapping = Niflect::MakeShared<CAccessorBindingMapping2>();
		auto& vecSetting = accessorBindingMapping->m_vecAccessorBindingSetting;
		SRecursCollectingData recursCollectiingData{ aliasChain.Get(), vecSetting };
		this->CollectDataRecurs2(cursor, g_invalidCursor, taggedParent, context, recursCollectiingData);

		//#1, 检查AccessorType定义是否继承自CAccessor
		for (uint32 idx0 = 0; idx0 < vecSetting.size(); ++idx0)
		{
			auto& it0 = vecSetting[idx0];
			auto& aSubcursor = it0.GetAccessorTypeDecl();
			bool ok = this->VerifyDerivedFromCAccessor(aSubcursor.m_cursorDecl, aliasChain.Get());
			//if (!found)
			//{
			//	auto templateDecl = clang_getSpecializedCursorTemplate(foundDecl);//预留支持特化模板作Accessor, 还需要实现特化模板声明指定标记
			//	found = this->CheckDeclDerivedFromFieldBaseClass(templateDecl);
			//}
			if (!ok)
			{
				Niflect::CString str;
				GenerateTemplateInstanceCode(it0.m_subcursorRoot, str);
				GenLogError(context.m_log, NiflectUtil::FormatString("Accessor type must be derived from %s, %s", NiflectGenDefinition::NiflectFramework::AccessorTypeName::Field, str.c_str()));
				break;
			}
		}
		
		//#2, 检查BindingType是否重定义, 生成BindingType的查找表
		//todo: 1. 多维BindingType; 2. 特化; 3. 部分特化;
		auto& mapCursorToIndex = accessorBindingMapping->m_mapCursorToIndex;
		auto& mapCXTypeToIndex = accessorBindingMapping->m_mapCXTypeToIndex;
		for (uint32 idx0 = 0; idx0 < vecSetting.size(); ++idx0)
		{
			auto& it0 = vecSetting[idx0];
			bool ok = true;
			auto& bSubcursor = it0.GetBindingTypeDecl();//此处b不是bool前缀
			uint32 idxDupWith = INDEX_NONE;
			if (clang_getCursorKind(bSubcursor.m_cursorDecl) == CXCursor_NoDeclFound)
			{
				auto ret = mapCXTypeToIndex.insert({ bSubcursor.m_CXType, idx0 });
				ok = ret.second;
				idxDupWith = ret.first->second;
			}
			else
			{
				//不支持多维BindingType以非1维cursor查重, 原因
				//1. 多维cursor构成的复合key显复杂化
				//2. 所谓的维, 是一种避免特殊处理多维结构的定义方式, 如由用户指定第2维的类型为std::pair的Accessor, 可避免解析std::map的定义, 其std::pair类型在allocator的模板参数中指定
				//	因此1维外的BindingType, 在概念上是与1维的BindingType一体的
				auto ret = mapCursorToIndex.insert({ bSubcursor.m_cursorDecl, idx0 });
				ok = ret.second;
				idxDupWith = ret.first->second;
			}
			if (!ok)
			{
				Niflect::CString str0;
				GenerateTemplateInstanceCode(it0.m_subcursorRoot, str0);
				Niflect::CString str1;
				GenerateTemplateInstanceCode(vecSetting[idxDupWith].m_subcursorRoot, str1);
				GenLogError(context.m_log, NiflectUtil::FormatString("Duplicated accessor binding of %s with %s. Additionally, partial template specialization is not supported for binding types.", str0.c_str(), str1.c_str()));

				if (!context.m_log->m_opt.m_cachedItems)
					break;
			}
		}

		for (uint32 idx0 = 0; idx0 < vecSetting.size(); ++idx0)
		{
			auto& it0 = vecSetting[idx0];
			for (uint32 idx1 = 0; idx1 < it0.GetDimensionalBindingTypeDeclsCount(); ++idx1)
			{
				auto& bindingTypeDecl = it0.GetDimensionalBindingTypeDecl(idx1);
				if (bindingTypeDecl.m_CXType.kind == CXType_Pointer)
				{
					GenLogError(context.m_log, "Pointer is not supported");//todo: 支持任意指针类型无实际用途, 应支持特定类型的指针, 需要获取的信息如几维指针与原始类型, 计划加到如m_mapUserTypePointer1D中, 即将指针解释为专门的类型, 这种专门的指针需要Runtime内存管理
					break;
				}
			}
		}

		collectionData.m_aliasChain = aliasChain;
		collectionData.m_accessorBindingMapping = accessorBindingMapping;

		//for (auto& it : collectionData.m_vecBindingSetting)
		//{
		//	auto& typeDecl = it.GetBindingTypeDecl();
		//	if (clang_getCursorKind(typeDecl.m_cursorDecl) != CXCursor_NoDeclFound)
		//	{
		//		auto decl = this->FindAliasDecl(typeDecl.m_cursorDecl);
		//		auto ret = collectionData.m_mapAliasTemplateDeclToClassTemplateCursor.insert({ typeDecl.m_cursorDecl, decl });
		//		if (!ret.second)
		//		{
		//			GenLogError(context.m_log, NiflectUtil::FormatString("Duplicated binding type specified for %s. Additionally, partial template specialization is not supported for binding types.", CXStringToCString(clang_getCursorSpelling(typeDecl.m_cursorDecl)).c_str()));
		//			break;//todo: 处于2层for, 需要有另外的逻辑检查有错误则不遍历sibling
		//		}
		//	}
		//}

		//for (auto& it : collectionData.m_vecBindingSetting)
		//{
		//	//auto a = it.GetBindingTypeDecl().GetTypeName();
		//	//printf("%s\n", a.c_str());

		//	auto& accessorCursorDecl = it.GetAccessorTypeDecl().m_cursorDecl;
		//	//auto itFound = m_mapCursorDeclToBaseCursorDecl.find(accessorCursorDecl);
		//	//ASSERT(itFound != m_mapCursorDeclToBaseCursorDecl.end());
		//	//it.m_accessorBaseCursorDecl = clang_getTypeDeclaration(clang_getCursorType(itFound->second));

		//	//auto p = it.m_accessorBaseCursorDecl;
		//	//bool isDerivedFromField = false;
		//	//while (true)
		//	//{
		//	//	auto name = CXStringToCString(clang_getCursorSpelling(p));
		//	//	if (name == NiflectGenDefinition::NiflectFramework::AccessorTypeName::Field)
		//	//	{
		//	//		isDerivedFromField = true;
		//	//		break;
		//	//	}
		//	//	auto itFound = m_mapCursorDeclToBaseCursorDecl.find(p);
		//	//	if (itFound != m_mapCursorDeclToBaseCursorDecl.end())
		//	//		p = clang_getTypeDeclaration(clang_getCursorType(itFound->second));
		//	//	else
		//	//		break;
		//	//}
		//	//if (!isDerivedFromField)
		//	//{
		//	//	GenLogError(context.m_log, NiflectUtil::FormatString("Accessor type must be derived from %s", NiflectGenDefinition::NiflectFramework::AccessorTypeName::Field));
		//	//	break;
		//	//}

		//	auto decl = this->FindAliasDecl(accessorCursorDecl);
		//	bool found = this->CheckDeclDerivedFromFieldBaseClass(decl);
		//	if (!found)
		//	{
		//		auto templateDecl = clang_getSpecializedCursorTemplate(decl);//预留支持特化模板作Accessor, 还需要实现特化模板声明指定标记
		//		found = this->CheckDeclDerivedFromFieldBaseClass(templateDecl);
		//	}
		//	if (!found)
		//	{
		//		GenLogError(context.m_log, NiflectUtil::FormatString("Field type must be derived from %s", NiflectGenDefinition::NiflectFramework::AccessorTypeName::Field));
		//		break;
		//	}

		//	it.m_actualFieldDeclCursor = decl;

		//	ASSERT(!it.m_accessorData.m_isNotATemplate);
		//	it.m_accessorData.m_isNotATemplate = !IsCursorTemplateDecl(it.GetBindingTypeDecl().m_cursorDecl);

		//	for (uint32 idx1 = 0; idx1 < it.GetDimensionalBindingTypeDeclsCount(); ++idx1)
		//	{
		//		auto& bindingTypeDecl = it.GetDimensionalBindingTypeDecl(idx1);
		//		if (bindingTypeDecl.m_CXType.kind == CXType_Pointer)
		//		{
		//			GenLogError(context.m_log, "Pointer is not supported");//todo: 支持任意指针类型无实际用途, 应支持特定类型的指针, 需要获取的信息如几维指针与原始类型, 计划加到如m_mapUserTypePointer1D中, 即将指针解释为专门的类型, 这种专门的指针需要Runtime内存管理
		//			break;
		//		}
		//	}
		//}
	}
	void CDataCollector::CollectDataRecurs2(const CXCursor& cursor, const CXCursor& parentCursor, CTaggedNode2* taggedParent, CCollectingContext& context, SRecursCollectingData& recursCollectiingData)
	{
		if (auto debugData = context.m_debugData)
		{
			debugData->m_allCursorsCount++;
			DebugPrintCursor(debugData->m_fp, cursor, debugData->m_level);
		}

		SVisitorCallbackData visitorCbData{this, taggedParent, context, recursCollectiingData.m_aliasChain };
		clang_visitChildren(cursor, &VisitorCallback, &visitorCbData);

		CScopeBindingSetting scopeBindingSetting(*this, cursor, visitorCbData.m_vecCursorChild, context, recursCollectiingData);

		TSharedPtr<CScopeAccessorBaseCursorDecl> scopeCollectingClassBaseCursorDecl;
		TSharedPtr<CScopeTemplateDecl> scopeCollectingAliasTemplateAndClassTemplateDecl;
		if (m_collectingClassBaseCursorDecl)
		{
			scopeCollectingClassBaseCursorDecl = MakeShared<CScopeAccessorBaseCursorDecl>(*this, cursor, visitorCbData.m_vecCursorChild);
			scopeCollectingAliasTemplateAndClassTemplateDecl = MakeShared<CScopeTemplateDecl>(cursor, visitorCbData.m_vecCursorChild, parentCursor, recursCollectiingData.m_aliasChain);
		}

		if (auto debugData = context.m_debugData)
			debugData->m_level++;

		for (uint32 idx = 0; idx < visitorCbData.m_vecCursorChild.size(); ++idx)
		{
			auto taggedChild = taggedParent;
			auto& taggedChildIndex = visitorCbData.m_visitingData.m_vecTaggedChildIndex[idx];
			if (taggedChildIndex != INDEX_NONE)
				taggedChild = taggedParent->GetChild(taggedChildIndex);
			this->CollectDataRecurs2(visitorCbData.m_vecCursorChild[idx], cursor, taggedChild, context, recursCollectiingData);
		}

		if (auto debugData = context.m_debugData)
			debugData->m_level--;
	}
	void DebugPrintTaggedNodeRecurs3(CTaggedNode2* taggedParent, int level)
	{
		taggedParent->DebugPrint(NULL, level);

		level++;
		for (auto& it0 : taggedParent->DebugGetChildren())
		{
			DebugPrintTaggedNodeRecurs3(it0.Get(), level);
		}
	}
	void CDataCollector::DebugFinish2(CTaggedNode2* taggedParent, const CCollectionData& collectionData) const
	{
		//if (true)
		//{
		//	for (auto& it : collectionData.m_vecBindingSetting)
		//	{
		//		PrintSubcursorRecurs(it.m_subcursorRoot);
		//		//ASSERT(it.m_subCursorRoot.m_vecChild.size() == 2);
		//		printf("---------\n");
		//	}
		//}
		//DebugPrintTaggedNodeRecurs2(taggedParent, 0);
		DebugPrintTaggedNodeRecurs3(taggedParent, 0);
	}
}