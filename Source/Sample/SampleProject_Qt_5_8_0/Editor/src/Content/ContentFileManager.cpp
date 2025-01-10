#include "Content/ContentFileManager.h"

namespace Wishing
{
	CContentNode* CContentFileManager::GetRootNode()
	{
		return &m_rootNode;
	}
	bool CContentFileManager::InsertNode(const CSharedContentNode& node, uint32 idx)
	{
		m_vecContentNode.insert(m_vecContentNode.begin() + idx, node);
		return true;
	}
	void CContentFileManager::DeleteNode(uint32 idx)
	{
		m_vecContentNode.erase(m_vecContentNode.begin() + idx);
	}
}