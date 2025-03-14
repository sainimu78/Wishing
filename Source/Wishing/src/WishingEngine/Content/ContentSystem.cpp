#include "WishingEngine/Content/ContentSystem.h"

namespace Wishing
{
	CContentSystem::CContentSystem()
		: m_rootDirNode(Niflect::MakeShared<CContentDirNode2>())
	{
	}
	bool CContentSystem::Initialize()
	{
		return true;
	}
	bool CContentSystem::Start()
	{
		return true;
	}
	bool CContentSystem::Stop()
	{
		return true;
	}
	void CContentSystem::Finalize()
	{

	}
	CContentDirNode2* CContentSystem::GetRootDirNode() const
	{
		return m_rootDirNode.Get();
	}
	void CContentSystem::AddFileNode(const CSharedContentFileNode2& node)
	{
		m_vecFileNode.push_back(node);
	}
	void CContentSystem::AddDirNode(const CSharedContentDirNode2& node)
	{
		m_vecDirNode.push_back(node);
	}

	CSharedContentSystem CreateContentSystem()
	{
		return Niflect::MakeShared<CContentSystem>();
	}
}