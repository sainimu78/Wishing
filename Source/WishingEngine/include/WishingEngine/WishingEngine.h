#pragma once
#include "WishingEngineCommon.h"
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
		WISHINGENGINE_API void Initialize();

	public:
		WISHINGENGINE_API bool RegisterObject(CWishingObject* obj);

	public:
		WISHINGENGINE_API CContentNodeManager* GetContentNodeManager() { return &m_contentNodeMgr; }

	private:
		Niflect::TArray<CWishingObject*> m_vecObject;
		CContentNodeManager m_contentNodeMgr;
	};
	using CSharedWishingEngine = Niflect::TSharedPtr<CWishingEngine>;

	WISHINGENGINE_API CSharedWishingEngine CreateWishingEngine();
}