#include "WishingEngine/WishingEngine.h"
#include "WishingEngine_private.h"

namespace Wishing
{
	CWishingEngine::CWishingEngine()
	{
		auto mgr = Niflect::GetModuleManager();
		mgr->InitRegisteredModules();
	}
	CWishingEngine::~CWishingEngine()
	{
	}
	void CWishingEngine::Initialize()
	{
		this->RegisterObject(&m_contentNodeMgr);
	}
	bool CWishingEngine::RegisterObject(CWishingObject* obj)
	{
		m_vecObject.push_back(obj);
		return true;
	}
	CSharedWishingEngine CreateWishingEngine()
	{
		return Niflect::MakeShared<CWishingEngine>();
	}
}