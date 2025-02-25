#include "WishingEngine/WishingEngine.h"
#include "Niflect/Base/SharedPtr.h"
#include "WishingEngine_private.h"

namespace Wishing
{
	static Niflect::TSharedPtr<CWishingEngine> g_engine;
	void InitializeWishingEngine()
	{
		ASSERT(g_engine == NULL);
		g_engine = Niflect::MakeShared<CWishingEngine>();

		auto mgr = Niflect::GetModuleManager();
		printf("Modules count: %u\n", mgr->GetModulesCount());
	}
	void FinalizeeWishingEngine()
	{
		g_engine = NULL;
		Niflect::FinalizeModuleManager();
	}
	CWishingEngine* GetWishingEngine()
	{
		return g_engine.Get();
	}
}