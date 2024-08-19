#include "NiflectGen/Resolver/Resolver.h"
#include "Niflect/Util/DebugUtil.h"
#include <algorithm>
#include "Niflect/Util/TypeUtil.h"

namespace NiflectGen
{
	using namespace Niflect;

	CResolver::CResolver(const CCollectionData& collectionData, const Niflect::TArrayNif<Niflect::CString>& vecHeaderSearchPath)
		: m_collectionData(collectionData)
		//, m_vecHeaderSearchPath(vecHeaderSearchPath)
		, m_foundCursorsCount(0)
	{
	}
	//void CResolver::Resolve(CTaggedNode2* taggedRoot, CResolvingContext& context, CResolvedData& data)
	//{
	//	this->ResolveRecurs(taggedRoot, context, data);

	//	//for (auto& it : m_collectionData.m_vecTemplateSubcursorRoot)
	//	//{
	//	//	auto accessorCursor = clang_getTypeDeclaration(it.m_vecChild[0].m_type);
	//	//	auto accessorTypeName = CXStringToCString(clang_getCursorSpelling(accessorCursor));
	//	//	CXType bindingType = it.m_vecChild[1].m_vecChild[0].m_type;
	//	//	auto bindingTypeCursor = clang_getTypeDeclaration(bindingType);
	//	//	auto bindingTypeName = CXStringToCString(clang_getCursorSpelling(bindingTypeCursor));
	//	//	//auto bindingTypeName = CXStringToCString(clang_getTypeSpelling(bindingType));
	//	//	printf("%s <-> %s\n", accessorTypeName.c_str(), bindingTypeName.c_str());
	//	//}

	//	for (auto& it0 : m_collectionData.m_vecBindingSetting)
	//	{
	//		if (!it0.IsValidBindingSetting())
	//		{
	//			GenLogError(context.m_log, "Unable to obtain type bindings from the TBindingSetting template instance");
	//			break;
	//		}
	//		auto accessorCursor = clang_getTypeDeclaration(it0.GetAccessorType());
	//		auto itFoundTaggedType = data.m_mapDeclarationToTaggedType.find(accessorCursor);
	//		if (itFoundTaggedType == data.m_mapDeclarationToTaggedType.end())
	//		{
	//			if (false)
	//			{
	//				//现不支持指定的类型带有模板类型Scope, 如下定义, m_mapDeclarationToTaggedType中的key为模板定义, 而accessorCursor则为模板实例, 因此用accessorCursor查找失败

	//				//template <typename T>
	//				//class CFieldTestMyTemplate : public Niflect::CFieldAccessor
	//				//{
	//				//public:
	//				//	NIF_T()
	//				//		class CSubMy2 : public Niflect::CFieldAccessor
	//				//	{
	//				//	};
	//				//};
	//				// 
	//				//NIF_BS() TBindingSetting2<MySub::CFieldTestMyTemplate<float>::CSubMy2, TTypeTuple<char> >;

	//				for (auto& it000 : data.m_mapDeclarationToTaggedType)
	//				{
	//					auto a = CXStringToCString(clang_getCursorSpelling(it000.first));
	//					if (a == "CSubMy2")
	//					{
	//						auto b = clang_equalCursors(it000.first, accessorCursor);//结果为, false
	//						auto c = CXStringToCString(clang_getCursorDisplayName(accessorCursor));
	//						auto d = CXStringToCString(clang_getCursorDisplayName(it000.first));
	//						auto e = clang_getCursorType(accessorCursor);
	//						auto f = clang_getCursorType(it000.first);
	//						auto g = CXStringToCString(clang_getTypeSpelling(e));//结果为, MyTestClassScope::MySub::CFieldTestMyTemplate<float>::CSubMy2
	//						auto h = CXStringToCString(clang_getTypeSpelling(f));//结果为, MyTestClassScope::MySub::CFieldTestMyTemplate::CSubMy2
	//						printf("");
	//					}
	//					printf("%s\n", a.c_str());
	//				}
	//			}

	//			//todo: 现要求Accessor必须带标记, 查找失败有3种情况
	//			//1. Accessor未加标记
	//			//2. 没有定义Accessor, 即代码本身无法编译
	//			//3. 使用模板实例Scope
	//			//计划改为要求Accessor必须从3个基本Accessor继承, 代码生成根据鸡肋生成代码即可, 区分是否为数组则无须其它标记

	//			GenLogError(context.m_log, "The bound accessor type is not tagged");//, or not defined
	//			break;
	//		}
	//		auto& taggedAccessorType = itFoundTaggedType->second;
	//		for (auto& it1 : it0.GetBindingTypesData())
	//		{
	//			const auto& bindingType = it1.m_type;
	//			auto bindingTypeCursor = clang_getTypeDeclaration(bindingType);
	//			bool ok = false;
	//			if (clang_getCursorKind(bindingTypeCursor) == CXCursor_NoDeclFound)
	//			{
	//				if (bindingType.kind == CXType_Pointer)
	//				{
	//					GenLogError(context.m_log, "Pointer is not supported");//todo: 支持任意指针类型无实际用途, 应支持特定类型的指针, 需要获取的信息如几维指针与原始类型, 计划加到如m_mapUserTypePointer1D中, 即将指针解释为专门的类型, 这种专门的指针需要Runtime内存管理
	//					break;//todo: 处于2层for, 需要有另外的逻辑检查有错误则不遍历sibling
	//				}
	//				else
	//				{
	//					ok = data.m_accessorTypeTable.m_mapBuiltinTypeKind.insert({ bindingType.kind, taggedAccessorType }).second;
	//					if (ok)
	//					{
	//						for (uint32 idx2 = 0; idx2 < data.m_vecResolvedTypes.size(); ++idx2)
	//						{
	//							bool found = false;
	//							auto& vec = data.m_vecResolvedTypes[idx2].m_vecResolvedTaggedType;
	//							for (uint32 idx3 = 0; idx3 < vec.size(); ++idx3)
	//							{
	//								auto& resolvedTaggedType = vec[idx3];
	//								ASSERT(resolvedTaggedType.m_taggedType != NULL);
	//								if (resolvedTaggedType.m_taggedType == taggedAccessorType)
	//								{
	//									ASSERT(false);//m_isBuiltinType已移除
	//									//ASSERT(!resolvedTaggedType.m_isBuiltinType);
	//									//resolvedTaggedType.m_isBuiltinType = true;//todo: 可能无必要, 由于解析时已按照用户的BindingSetting.h中include DFS, 因此builtin类型的accessor一定在其它依赖builtin类型的类型之前
	//									found = true;
	//									break;
	//								}
	//							}
	//							if (found)
	//								break;
	//						}
	//					}
	//				}
	//			}
	//			else
	//			{
	//				ok = data.m_accessorTypeTable.m_mapUserType.insert({ bindingTypeCursor, taggedAccessorType }).second;
	//			}
	//			if (!ok)
	//			{
	//				GenLogError(context.m_log, "Binding types are conflicting, an identical binding type is expected for an accessor");
	//				break;//todo: 处于2层for, 需要有另外的逻辑检查有错误则不遍历sibling
	//			}
	//		}
	//	}
	//}
	//void CResolver::ResolveRecurs(CTaggedNode2* taggedParent, CResolvingContext& context, CResolvedData& data)
	//{
	//	if (auto taggedType = CTaggedType::CastChecked(taggedParent))
	//	{
	//		auto& cursor = taggedType->GetCursor();
	//		{
	//			auto loc = clang_getCursorLocation(cursor);
	//			CXFile file;
	//			clang_getSpellingLocation(loc, &file, NULL, NULL, NULL);
	//			auto filePathAbs = CXStringToCString(clang_getFileName(file));
	//			std::replace(filePathAbs.begin(), filePathAbs.end(), '\\', '/');
	//			auto ret = m_mapFilePathToResolvedTypeIndex.insert({ filePathAbs, static_cast<uint32>(data.m_vecResolvedTypes.size()) });
	//			if (ret.second)
	//			{
	//				CResolvedTypes item;
	//				item.m_filePathAbs = filePathAbs;
	//				bool foundPrefix = false;
	//				for (auto& it : m_vecHeaderSearchPath)
	//				{
	//					ASSERT(!it.empty());
	//					auto pos = filePathAbs.find(it);
	//					if (pos != std::string::npos)
	//					{
	//						auto prefixLength = pos + it.length();
	//						item.m_filePathRelativeToHeaderSearchPath = filePathAbs.substr(prefixLength + 1, filePathAbs.length() - prefixLength);
	//						foundPrefix = true;
	//						break;
	//					}
	//				}
	//				if (!foundPrefix)
	//				{
	//					GenLogError(context.m_log, "Unable to resolve the header relative path");
	//					return;//todo: 处于递归, 需要有另外的逻辑检查有错误则不遍历sibling
	//				}
	//				data.m_vecResolvedTypes.emplace_back(item);
	//			}
	//			auto& item = data.m_vecResolvedTypes[ret.first->second];
	//			item.m_vecResolvedTaggedType.push_back(taggedType);
	//		}
	//		ASSERT(clang_isDeclaration(clang_getCursorKind(cursor)));
	//		auto ret = data.m_mapDeclarationToTaggedType.insert({ cursor, taggedType });
	//		if (!ret.second)
	//		{
	//			GenLogError(context.m_log, "Tagged type collection goes wrong");
	//			return;//todo: 处于递归, 需要有另外的逻辑检查有错误则不遍历sibling
	//		}
	//	}

	//	for (auto& it0 : taggedParent->DebugGetChildren())
	//	{
	//		this->ResolveRecurs(it0.Get(), context, data);
	//	}
	//}
	void CResolver::Resolve2(CTaggedNode2* taggedRoot, CResolvingContext& context, CResolvedData& data)
	{
		auto& accessorBindingMapping = data.m_mapping.m_accessorBindingMapping;
		for (auto& it0 : m_collectionData.m_vecBindingSetting)
		{
			if (!it0.IsValidBindingSetting())
			{
				GenLogError(context.m_log, "Unable to obtain type bindings from the TBindingSetting template instance");
				break;
			}
			
			auto accessorBindingIndex = static_cast<uint32>(accessorBindingMapping.m_vecAccessorBinding2.size());

			bool ok = false;
			auto& bindingTypeDecl = it0.GetBindingTypeDecl();
			if (clang_getCursorKind(bindingTypeDecl.m_cursorDecl) == CXCursor_NoDeclFound)
			{
				ok = accessorBindingMapping.m_mapBasicTypeKindToAccessorBindingIndex.insert({ bindingTypeDecl.m_CXType.kind, {accessorBindingIndex, bindingTypeDecl.m_CXType} }).second;
			}
			else
			{
				auto cursorDecl = bindingTypeDecl.m_cursorDecl;
				bool declValid = true;
				auto kind = clang_getCursorKind(cursorDecl);
				if ((kind == CXCursor_TypeAliasTemplateDecl) || (kind == CXCursor_TypeAliasDecl))
				{
					auto itFound = m_collectionData.m_mapAliasTemplateDeclToClassTemplateCursor.find(cursorDecl);
					if (itFound != m_collectionData.m_mapAliasTemplateDeclToClassTemplateCursor.end())
					{
						cursorDecl = itFound->second;
					}
					else
					{
						declValid = false;
					}
				}

				if (declValid)
				{
					ok = accessorBindingMapping.m_mapBasicCusorDeclToAccessorBindingIndex.insert({ bindingTypeDecl.m_cursorDecl, accessorBindingIndex }).second;
					//ok = accessorBindingMapping.m_mapBasicCusorDeclToAccessorBindingIndex.insert({ cursorDecl, accessorBindingIndex }).second;//原始Decl, 留作备用
				}
			}
			if (!ok)
			{
				GenLogError(context.m_log, "Binding types are conflicting, an identical binding type is expected for an accessor");
				break;//todo: 处于2层for, 需要有另外的逻辑检查有错误则不遍历sibling
			}

			CAccessorBinding item(it0.GetAccessorTypeDecl(), it0.m_actualFieldDeclCursor, it0.m_accessorData);
			for (uint32 idx1 = 0; idx1 < it0.GetDimensionalBindingTypeDeclsCount(); ++idx1)
			{
				auto& bindingTypeDecl = it0.GetDimensionalBindingTypeDecl(idx1);
				item.m_vecWWWW.push_back(bindingTypeDecl);
			}
			//auto a = CXStringToCString(clang_getCursorSpelling(item.m_accessorCursorDecl));
			//printf("%s\n", a.c_str());
			accessorBindingMapping.m_vecAccessorBinding2.emplace_back(item);
		}

		//todo: 可简化, 实际上只有非模板cursor才有可能具有TaggedNode
		for (auto& it0 : accessorBindingMapping.m_vecAccessorBinding2)
		{
			auto ret = m_mapAccessorCursorDeclToAccessorBindingIndex.insert({ it0.m_accessorSubcursor.m_cursorDecl, &it0.m_accessorTaggedType });
			if (!ret.second)
			{
				GenLogError(context.m_log, "Accessor types are conflicting, an identical binding is expected");
				break;//todo: 处于2层for, 需要有另外的逻辑检查有错误则不遍历sibling
			}
			//for (auto& it1 : it0.m_vecWWWW)
			//{
			//	auto ret = m_mapAccessorCursorDeclToAccessorBindingIndex.insert({ it1.m_subcursor.m_cursorDecl, &it1.m_untaggedType });
			//	if (!ret.second)
			//	{
			//		for (auto& ssssssss : m_mapAccessorCursorDeclToAccessorBindingIndex)
			//		{
			//			auto a = CXStringToCString(clang_getCursorSpelling(ssssssss.first));
			//			printf("%s\n", a.c_str());
			//		}
			//		auto a = CXStringToCString(clang_getCursorSpelling(it1.m_subcursor.m_cursorDecl));
			//		printf("%s\n", a.c_str());

			//		GenLogError(context.m_log, "Accessor types are conflicting, an identical binding is expected");
			//		break;//todo: 处于2层for, 需要有另外的逻辑检查有错误则不遍历sibling
			//	}
			//}
		}

		this->ResolveRecurs2(taggedRoot, context, data);

		ASSERT(m_foundCursorsCount <= accessorBindingMapping.m_vecAccessorBinding2.size());

		//for (auto& it0 : accessorBindingMapping.m_vecAccessorBinding2)
		//{
		//	auto a = CXStringToCString(clang_getCursorSpelling(it0.m_accessorCursorDecl));
		//	printf("%s\n", a.c_str());
		//}

		//未实现按CursorDeclaration依赖顺序遍历, 因此在最后ResolveDependcies
		for (auto& it : data.m_vecResolvedTypes2)
			it.m_taggedType->ResolveDependcies(data.m_mapping.m_mapCursorDeclToTaggedType);
	}
	void CResolver::ResolveRecurs2(CTaggedNode2* taggedParent, CResolvingContext& context, CResolvedData& data)
	{
		if (auto taggedType = CTaggedType::CastChecked(taggedParent))
		{
			auto& cursor = taggedType->GetCursor();
			ASSERT(clang_isDeclaration(clang_getCursorKind(cursor)));
			//auto ret = m_mapCusorDeclToTaggedType.insert({ cursor, taggedType });
			//if (!ret.second)
			//{
			//	GenLogError(context.m_log, "Tagged type collection goes wrong");
			//	return;//todo: 处于递归, 需要有另外的逻辑检查有错误则不遍历sibling
			//}
			//bool isAccessorCursorDecl = false;
			//if (m_foundCursorsCount < data.m_vecAccessorBinding2.size())
			//{
			//	auto itFound = m_mapAccessorCursorDeclToIndex.find(cursor);
			//	if (itFound != m_mapAccessorCursorDeclToIndex.end())
			//	{
			//		auto& item = data.m_vecAccessorBinding2[itFound->second];
			//		ASSERT(item.m_accesorTaggedType == NULL);
			//		item.m_accesorTaggedType = taggedType;
			//		m_foundCursorsCount++;
			//		isAccessorCursorDecl = true;
			//	}
			//}
			//if (!isAccessorCursorDecl)
			//{
			//	data.m_vecResolvedTypes2.push_back(taggedType);
			//}

			auto& accessorBindingMapping = data.m_mapping.m_accessorBindingMapping;
			bool isAccessorCursorDecl = false;
			if (m_foundCursorsCount < accessorBindingMapping.m_vecAccessorBinding2.size())
			{
				auto itFound = m_mapAccessorCursorDeclToAccessorBindingIndex.find(cursor);
				if (itFound != m_mapAccessorCursorDeclToAccessorBindingIndex.end())
				{
					ASSERT(*itFound->second == NULL);
					*itFound->second = taggedType;
					m_foundCursorsCount++;
					isAccessorCursorDecl = true;
				}
			}
			if (!isAccessorCursorDecl)
			{
				data.m_vecResolvedTypes2.push_back(taggedType);
			}
			//auto a = CXStringToCString(clang_getCursorSpelling(cursor));
			//printf("%s\n", a.c_str());
			data.m_mapping.m_mapCursorDeclToTaggedType.insert({ cursor, taggedType });
		}
		else if (auto untaggedType = Niflect::CastChecked<CUntaggedTemplate>(taggedParent))
		{
			auto& cursor = untaggedType->GetCursor();
			data.m_mapping.m_mapCursorDeclToUntaggedTemplate.insert({ cursor, untaggedType });
		}

		for (auto& it0 : taggedParent->DebugGetChildren())
		{
			this->ResolveRecurs2(it0.Get(), context, data);
		}
	}
	//void CResolver::DebugFinish(const CResolvedData& data) const
	//{
	//	for (auto& it : data.m_accessorTypeTable.m_mapBuiltinTypeKind)
	//	{
	//		auto a = CXStringToCString(clang_getTypeKindSpelling(it.first));
	//		auto b = CXStringToCString(clang_getCursorSpelling(it.second->GetCursor()));
	//		printf("%s <-> %s\n", a.c_str(), b.c_str());
	//	}
	//	printf("");
	//	for (auto& it : data.m_accessorTypeTable.m_mapUserType)
	//	{
	//		auto a = CXStringToCString(clang_getCursorSpelling(it.first));
	//		auto b = CXStringToCString(clang_getCursorSpelling(it.second->GetCursor()));
	//		printf("%s <-> %s\n", a.c_str(), b.c_str());
	//	}
	//	printf("");
	//}

	// 预想的Resolve功能是解决类型依赖, 或其它生成代码的准备功能, 如将TaggedNode按依赖顺序排序
	// C++语法中仅枚举支持只声明即可使用, 但这种用法完全无必要支持
	// 因此暂不以依赖顺序生成代码, 使用的顺序完全基于入口源码
	//以下为备用代码, 可生成依赖顺序的TaggedNode队列
	
	TSharedPtr<TCursorMap<CTaggedType*> > g_my_unordered_map;//定义成指针仅为避免未使用时占用的内存(静态占用)
	void DDDDDDDDDDDDDDDDDRecurs(CTaggedNode2* taggedParent, int level)
	{
		if (g_my_unordered_map == NULL)
			g_my_unordered_map = MakeShared<TCursorMap<CTaggedType*> >();

		auto& my_unordered_map = *g_my_unordered_map;
		if (auto taggedType = CTaggedType::CastChecked(taggedParent))
			my_unordered_map[taggedType->GetCursor()] = taggedType;


		//auto strLevel = NiflectUtil::DebugIndentToString(level);

		//auto& cursor = taggedParent->DebugGetCursor();
		//auto strName = CXStringToCString(clang_getCursorSpelling(cursor));
		//auto type = clang_getCursorType(cursor);
		//auto strType = CXStringToCString(clang_getTypeSpelling(type));
		//printf("%s%s, %s\n", strLevel.c_str(), strName.c_str(), strType.c_str());


		level++;

		for (auto& it0 : taggedParent->DebugGetChildren())
		{
			DDDDDDDDDDDDDDDDDRecurs(it0.Get(), level);
		}
	}
	void DDDDDDDDDDDDDDDDDRecurs2(CTaggedNode2* taggedParent, TArrayNif<CTaggedType*>& vecOrderedType, TSet<CTaggedType*>& setAdded, int level)
	{
		auto& my_unordered_map = *g_my_unordered_map;
		auto taggedType = CTaggedType::CastChecked(taggedParent);
		if (taggedType != NULL)
		{
			if (!setAdded.insert(taggedType).second)
				return;
		}
		else
		{
		}

		{
			auto& cursor = taggedParent->GetCursor();
			auto type = clang_getCursorType(cursor);
			type = GetPointerOriginalType(type);
			auto typeCursor = clang_getTypeDeclaration(type);
			auto itFound = my_unordered_map.find(typeCursor);
			if (itFound != my_unordered_map.end())
			{
				DDDDDDDDDDDDDDDDDRecurs2(itFound->second, vecOrderedType, setAdded, level);
			}
			else
			{
				//root或builtin
			}
		}

		for (auto& it0 : taggedParent->DebugGetChildren())
		{
			DDDDDDDDDDDDDDDDDRecurs2(it0.Get(), vecOrderedType, setAdded, level);
		}

		if (taggedType != NULL)
		{
			//vecOrderedType.insert(vecOrderedType.begin(), taggedType);
			vecOrderedType.push_back(taggedType);
		}
	}
	void SortTaggedNodesInDependencyOrder(CTaggedNode2* taggedParent, Niflect::TArrayNif<CTaggedType*>& vecOrderedType)
	{
		DDDDDDDDDDDDDDDDDRecurs(taggedParent, 0);
		TSet<CTaggedType*> setAdded;
		DDDDDDDDDDDDDDDDDRecurs2(taggedParent, vecOrderedType, setAdded, 0);
	}
}