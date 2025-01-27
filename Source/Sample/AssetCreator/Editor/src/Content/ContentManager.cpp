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
	static void InsertNode(CContentDirNode* parentNode, const CSharedContentNode& shared, const Niflect::CString& name, Niflect::TArray<CSharedContentNode>& m_vecNode, CContentEditContext& ctx)
	{
		auto tableIdx = static_cast<uint32>(m_vecNode.size());
		m_vecNode.push_back(shared);
		auto node = shared.Get();
		node->Init(name, tableIdx);
		parentNode->AddChild(node);
		ctx.MarkExistingDirty(node);
	}
	CContentDirNode* CContentManager::InsertDirNode(const Niflect::CString& name, CContentDirNode* parentNode, CContentEditContext& ctx)
	{
		auto dirNode = Niflect::MakeShared<CContentDirNode>();
		InsertNode(parentNode, dirNode, name, m_vecNode, ctx);
		return dirNode.Get();
	}
	CContentFileNode* CContentManager::InsertFileNode(const Niflect::CString& name, CContentDirNode* parentNode, CContentEditContext& ctx)
	{
		auto fileNode = Niflect::MakeShared<CContentFileNode>();
		InsertNode(parentNode, fileNode, name, m_vecNode, ctx);
		return fileNode.Get();
	}
	void CContentManager::DeleteNode(CContentNode* node, CContentEditContext& ctx)
	{
		auto& tableIdx = node->GetTableIndex();
		auto shared = m_vecNode[tableIdx];
		m_vecNode.erase(m_vecNode.begin() + tableIdx);
		ctx.MarkDeletingDirty(shared);
	}
	static void CreateNodePathRecurs(const Niflect::TArray<Niflect::CString>& vecName, uint32 frontIdx)
	{

	}
	void CContentManager::CreateFileNodePath(const Niflect::CString& filePath, CContentEditContext& ctx)
	{
		auto parentDirPath = NiflectUtil::GetParentDirPath(filePath);

	}
}