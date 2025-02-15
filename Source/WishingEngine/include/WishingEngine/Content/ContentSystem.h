#pragma once
#include "WishingEngineCommon.h"
#include "Niflect/Base/SharedPtr.h"

namespace Wishing
{
	class CContentSystem
	{
	public:
		CContentSystem();

	public:
		WISHINGENGINE_API bool Initialize();
		WISHINGENGINE_API bool Start();
		WISHINGENGINE_API bool Stop();
		WISHINGENGINE_API void Finalize();
	};
	using CSharedContentSystem = Niflect::TSharedPtr<CContentSystem>;

	WISHINGENGINE_API CSharedContentSystem CreateContentSystem();
}