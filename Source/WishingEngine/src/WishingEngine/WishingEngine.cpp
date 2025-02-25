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
		Niflect::CleanupModuleManager();
	}
	void CWishingEngine::Initialize()
	{
	}
	CSharedWishingEngine CreateWishingEngine()
	{
		return Niflect::MakeShared<CWishingEngine>();
	}
}