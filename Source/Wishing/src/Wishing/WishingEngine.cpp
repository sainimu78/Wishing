#include "Wishing/WishingEngine.h"
#include "Wishing_private.h"

namespace Wishing
{
	CWishingEngine::CWishingEngine()
	{
		auto reg = Niflect::GetModuleRegistry();
		reg->InitRegisteredModules();
	}
	CWishingEngine::~CWishingEngine()
	{
	}
	void CWishingEngine::Initialize()
	{
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