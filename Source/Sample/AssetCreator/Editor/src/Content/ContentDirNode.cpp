#include "Content/ContentDirNode.h"

namespace Wishing
{
	void CContentDirNode::AddChild(CContentNode* node)
	{
		m_vecChild.push_back(node);
	}
	void CContentDirNode::DeleteChild(CContentNode* node)
	{
		auto itFound = std::find(m_vecChild.begin(), m_vecChild.end(), node);
		ASSERT(itFound != m_vecChild.end());
		m_vecChild.erase(itFound);
	}
	//uint32 CContentNode::FindChildIndex(const Niflect::CString& name) const
	//{
	//	for (uint32 idx = 0; idx < m_vecChild.size(); ++idx)
	//	{
	//		if (m_vecChild[idx]->m_name == name)
	//			return idx;
	//	}
	//	return INDEX_NONE;
	//}
	CContentNode* CContentDirNode::FindChild(const Niflect::CString& name) const
	{
		for (auto& it : m_vecChild)
		{
			if (it->GetName() == name)
				return it;
		}
		return NULL;
	}
	CContentDirNode* CContentDirNode::FindChildDir(const Niflect::CString& name) const
	{
		if (auto found = this->FindChild(name))
		{
			ASSERT(CContentDirNode::CastChecked(found) != NULL);
			return CContentDirNode::Cast(found);
		}
		return NULL;
	}
	CContentFileNode* CContentDirNode::FindChildFile(const Niflect::CString& name) const
	{
		if (auto found = this->FindChild(name))
		{
			ASSERT(CContentFileNode::CastChecked(found) != NULL);
			return CContentFileNode::Cast(found);
		}
		return NULL;
	}
}