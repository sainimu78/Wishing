#include "Content/ContentFileSystem.h"

namespace Wishing
{
	CContentNode* CContentFileSystem::GetRootNode()
	{
		return &m_rootNode;
	}
	bool CContentFileSystem::InsertNode(const CSharedContentNode& node, uint32 idx)
	{
		m_vecContentNode.insert(m_vecContentNode.begin() + idx, node);
		return true;
	}
	void CContentFileSystem::DeleteNode(uint32 idx)
	{
		m_vecContentNode.erase(m_vecContentNode.begin() + idx);
	}
}