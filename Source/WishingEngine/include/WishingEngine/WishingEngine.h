#pragma once
#include "WishingEngineCommon.h"
#include "Niflect/Base/SharedPtr.h"

namespace Wishing
{
	class CWishingEngine
	{
	public:
		CWishingEngine();
		~CWishingEngine();

	public:
		WISHINGENGINE_API void Initialize();
	};
	using CSharedWishingEngine = Niflect::TSharedPtr<CWishingEngine>;

	WISHINGENGINE_API CSharedWishingEngine CreateWishingEngine();
}