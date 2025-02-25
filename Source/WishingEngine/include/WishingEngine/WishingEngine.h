#pragma once
#include "WishingEngineCommon.h"
#include "Niflect/Base/SharedPtr.h"
#include "WishingEngine/WishingObject.h"

namespace Wishing
{
	class CWishingEngine
	{
	public:
		CWishingEngine();
		~CWishingEngine();

	public:
		WISHINGENGINE_API void Initialize();

	public:
		WISHINGENGINE_API bool RegisterObject(CWishingObject* obj);

	private:
		Niflect::TArray<CWishingObject*> m_vecObject;
	};
	using CSharedWishingEngine = Niflect::TSharedPtr<CWishingEngine>;

	WISHINGENGINE_API CSharedWishingEngine CreateWishingEngine();
}