#include "Content/ContentNode.h"

namespace Wishing
{
	CContentNode::CContentNode()
		: m_parentNode(NULL)
		, m_tableIdx(INDEX_NONE)
	{

	}
	void CContentNode::Init(const Niflect::CString& name, uint32 tableIdx)
	{
		m_name = name;
		m_tableIdx = tableIdx;
	}
	void CContentNode::InitGlobalId(const CUuid& globalId)
	{
		ASSERT(!m_globalId.IsValid());
		m_globalId = globalId;
	}
	//void CContentNode::SetName(const Niflect::CString& name)
	//{
	//	m_name = name;
	//}
	//void CContentNode::SetParentNode(CContentNode* parentNode)
	//{
	//	m_parentNode = parentNode;
	//}
	//CContentNode* CContentNode::GetParentNode() const
	//{
	//	return m_parentNode;
	//}
	void CContentNode::AddNode(CContentNode* node)
	{
		m_vecNode.push_back(node);
	}
	void CContentNode::DeleteNode(CContentNode* node)
	{
		auto itFound = std::find(m_vecNode.begin(), m_vecNode.end(), node);
		ASSERT(itFound != m_vecNode.end());
		m_vecNode.erase(itFound);
	}
	CContentNode* CContentNode::FindNode(const Niflect::CString& name) const
	{
		for (auto& it : m_vecNode)
		{
			if (it->GetName() == name)
				return it;
		}
		return NULL;
	}
}