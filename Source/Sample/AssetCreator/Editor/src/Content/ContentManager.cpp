#include "Content/ContentManager.h"
#include "Content/ContentFileNode.h"
#include "Base/UuidGen.h"
#include "Niflect/Util/StringUtil.h"

namespace Wishing
{
	CContentDirNode* CContentManager::GetRootDirNode()
	{
		return &m_rootDirNode;
	}
	static void InitAddingNode(const CSharedContentNode& shared, const Niflect::CString& name, CContentDirNode* parentNode, Niflect::TArray<CSharedContentNode>& m_vecNode, CContentChangeContext& ctx)
	{
		auto tableIdx = static_cast<uint32>(m_vecNode.size());
		m_vecNode.push_back(shared);
		auto node = shared.Get();
		node->Init(name, parentNode, tableIdx);
		ctx.MarkExistingDirty(node);
	}
	CContentDirNode* CContentManager::AddDirNode(CContentDirNode* parentNode, const Niflect::CString& name, CContentChangeContext& ctx)
	{
		auto shared = Niflect::MakeShared<CContentDirNode>();
		InitAddingNode(shared, name, parentNode, m_vecNode, ctx);
		auto node = shared.Get();
		parentNode->AddDirNode(node);
		return node;
	}
	CContentFileNode* CContentManager::AddFileNode(CContentDirNode* parentNode, const Niflect::CString& name, CContentChangeContext& ctx)
	{
		auto shared = Niflect::MakeShared<CContentFileNode>();
		InitAddingNode(shared, name, parentNode, m_vecNode, ctx);
		auto node = shared.Get();
		parentNode->AddFileNode(node);
		return node;
	}
	void CContentManager::DeleteNode(CContentFileNode* node, CContentChangeContext& ctx)
	{
		auto& tableIdx = node->GetTableIndex();
		auto shared = m_vecNode[tableIdx];
		m_vecNode.erase(m_vecNode.begin() + tableIdx);
		ctx.MarkDeletingDirty(shared);
	}
	//CContentDirNode* CContentManager::FindDirNode(CContentDirNode* parent, const Niflect::CString& name) const
	//{
	//	for (auto& it : m_vecNode)
	//	{
	//		if (it->GetName() == name)
	//		{
	//			auto node = it.Get();
	//			if (auto dirNode = CContentDirNode::CastChecked(node))
	//				return dirNode;
	//		}
	//	}
	//	return NULL;
	//}
	CContentFileNode* CContentManager::FindOrCreateFileNodePath(const Niflect::CString& filePath, CContentChangeContext& ctx)
	{
		CContentDirNode* parentDirNode = this->GetRootDirNode();
		auto vecName = NiflectUtil::Split(filePath, '/');
		ASSERT(vecName.size() > 0);
		int32 cntDirCount = static_cast<int32>(vecName.size()) - 1;
		if (cntDirCount > 0)
		{
			for (int32 idx = 0; idx < cntDirCount; ++idx)
			{
				auto& name = vecName[idx];
				if (auto found = parentDirNode->FindDirNode(name))
					parentDirNode = found;
				else
					parentDirNode = this->AddDirNode(parentDirNode, name, ctx);
			}
			ASSERT(parentDirNode->GetName() == vecName[cntDirCount - 1]);
		}

		return this->AddFileNode(parentDirNode, vecName.back(), ctx);
	}
}