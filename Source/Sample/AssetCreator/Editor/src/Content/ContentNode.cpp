#include "Content/ContentNode.h"

namespace Wishing
{
	CContentNode::CContentNode()
		: m_parentNode(NULL)
	{

	}
	void CContentNode::InitGlobalId(const CUuid& globalId)
	{
		m_globalId = globalId;
	}
	void CContentNode::SetName(const Niflect::CString& name)
	{
		m_name = name;
	}
	void CContentNode::SetParentNode(CContentNode* parentNode)
	{
		m_parentNode = parentNode;
	}
	const Niflect::CString& CContentNode::GetName() const
	{
		return m_name;
	}
	CContentNode* CContentNode::GetParentNode() const
	{
		return m_parentNode;
	}
}