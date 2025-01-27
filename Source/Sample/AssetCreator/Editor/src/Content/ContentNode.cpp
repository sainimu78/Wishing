#include "Content/ContentNode.h"
#include <algorithm>

namespace Wishing
{
	CContentNode::CContentNode()
		: m_parentNode(NULL)
		, m_tableIdx(INDEX_NONE)
	{

	}
	void CContentNode::Init(const Niflect::CString& name, CContentDirNode* parentNode, uint32 tableIdx)
	{
		m_name = name;
		m_tableIdx = tableIdx;
		m_parentNode = parentNode;
	}
	void CContentNode::InitGlobalId(const CUuid& globalId)
	{
		ASSERT(!m_globalId.IsValid());
		m_globalId = globalId;
	}
}
