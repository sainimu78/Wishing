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
}