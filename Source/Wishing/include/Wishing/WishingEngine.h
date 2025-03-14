#pragma once
#include "WishingCommon.h"
#include "Niflect/Base/SharedPtr.h"
#include "Wishing/WishingObject.h"

namespace Wishing
{
	class CWishingEngine
	{
	public:
		CWishingEngine();
		~CWishingEngine();

	public:
		WISHING_API void Initialize();

	public:
		WISHING_API bool RegisterObject(CWishingObject* obj);

	private:
		Niflect::TArray<CWishingObject*> m_vecObject;
	};
	using CSharedWishingEngine = Niflect::TSharedPtr<CWishingEngine>;

	WISHING_API CSharedWishingEngine CreateWishingEngine();
}