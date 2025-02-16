#include "WishingEngine/Content/ContentEditingScope.h"
#include "WishingEngine/Content/ContentSystem.h"

namespace Wishing
{
	void CContentEditingScope::AddFileNode(const Niflect::CString& name, const CContentAddingOption& opt)
	{
		auto parent = opt.m_parent;
		if (parent == NULL)
			parent = m_sys->GetRootDirNode();
		
		auto node = Niflect::MakeShared<CContentFileNode2>();
		node->Init(name, parent);
		m_sys->AddFileNode(node);
		m_changed = true;
	}
}