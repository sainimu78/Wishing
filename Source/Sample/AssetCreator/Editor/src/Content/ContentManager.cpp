#include "Content/ContentManager.h"

namespace Wishing
{
	CContentNode* CContentManager::GetRootNode()
	{
		return &m_rootNode;
	}
	bool CContentManager::InsertNode(const CSharedContentNode& node, uint32 idx)
	{
		m_vecContentNode.insert(m_vecContentNode.begin() + idx, node);
		return true;
	}
	void CContentManager::DeleteNode(uint32 idx)
	{
		m_vecContentNode.erase(m_vecContentNode.begin() + idx);
	}
}