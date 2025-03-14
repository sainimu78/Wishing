#pragma once
#include "WishingCommon.h"
#include "Niflect/Base/SharedPtr.h"
#include "WishingEngine/WishingObject.h"
#include "WishingEngine/Content/ContentNodeManager.h"

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

	public:
		WISHING_API CContentNodeManager* GetContentNodeManager() { return &m_contentNodeMgr; }

	private:
		Niflect::TArray<CWishingObject*> m_vecObject;
		CContentNodeManager m_contentNodeMgr;
	};
	using CSharedWishingEngine = Niflect::TSharedPtr<CWishingEngine>;

	WISHING_API CSharedWishingEngine CreateWishingEngine();
}