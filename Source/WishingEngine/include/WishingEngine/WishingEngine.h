#pragma once
#include "WishingEngineCommon.h"

namespace Wishing
{
	class CWishingEngine
	{
	public:
	};

	WISHINGENGINE_API void InitializeWishingEngine();
	WISHINGENGINE_API void FinalizeWishingEngine();
	WISHINGENGINE_API CWishingEngine* GetWishingEngine();
}