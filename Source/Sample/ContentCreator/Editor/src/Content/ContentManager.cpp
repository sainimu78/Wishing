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
	void CContentManager::DeleteFileNode(CContentFileNode* node, CContentChangeContext& ctx)
	{
		auto& tableIdx = node->GetTableIndex();
		auto shared = m_vecNode[tableIdx];
		m_vecNode.erase(m_vecNode.begin() + tableIdx);
		ctx.MarkDeletingDirty(shared);
	}
	CContentFileNode* CContentManager::FindOrCreateFileNodePath(const Niflect::CString& filePath, CContentChangeContext& ctx)
	{
		CContentDirNode* parentDirNode = this->GetRootDirNode();
		auto vecName = NiflectUtil::SplitPath(filePath);
		ASSERT(vecName.size() > 0);
		int32 dirsCount = static_cast<int32>(vecName.size()) - 1;
		if (dirsCount > 0)
		{
			for (int32 idx = 0; idx < dirsCount; ++idx)
			{
				auto& name = vecName[idx];
				if (auto found = parentDirNode->FindDirNode(name))
					parentDirNode = found;
				else
					parentDirNode = this->AddDirNode(parentDirNode, name, ctx);
			}
			ASSERT(parentDirNode->GetName() == vecName[dirsCount - 1]);
		}

		return this->AddFileNode(parentDirNode, vecName.back(), ctx);
	}
	bool CContentManager::Save(RwTree::CRwNode* rw) const
	{
		using namespace RwTree;
		auto rwMyArray = AddRwArray(rw, "MyArray");
		for (auto& it : m_vecNode)
			rwMyArray->AddItemString(it->GetName());
		return true;
	}
	bool CContentManager::Load(const RwTree::CRwNode* rw)
	{
		return false;
	}
}