#include "WishingEngine/WishingEngine.h"
#include "Niflect/Base/SharedPtr.h"
#include "WishingEngine_private.h"

namespace Wishing
{
	static CWishingEngine* g_instance = NULL;
	CWishingEngine::CWishingEngine()
	{
		ASSERT(g_instance == NULL);
		g_instance = this;
	}
	CWishingEngine::~CWishingEngine()
	{
		Niflect::FinalizeModuleManager();
		g_instance = NULL;
	}
	void CWishingEngine::Initialize()
	{
		auto mgr = Niflect::GetModuleManager();
		mgr->InitRegisteredModules();
	}
	CSharedWishingEngine CreateWishingEngine()
	{
		return Niflect::MakeShared<CWishingEngine>();
	}
	CWishingEngine* GetWishingEngine()
	{
		return g_instance;
	}
}