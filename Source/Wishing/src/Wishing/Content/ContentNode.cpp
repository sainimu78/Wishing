#include "Wishing/Content/ContentNode.h"

namespace Wishing
{
	CContentNode2::CContentNode2()
		: m_parent(NULL)
	{

	}
	void CContentNode2::Init(const Niflect::CString& name, CContentNode2* parent)
	{
		m_name = name;
		m_parent = parent;
	}
}