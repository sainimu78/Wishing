#pragma once
#include "WishingCommon.h"
#include "Niflect/Base/SharedPtr.h"
#include "Wishing/Content/ContentGraph.h"

namespace Wishing
{
	class CContentSystem
	{
	public:
		CContentSystem();

	public:
		WISHING_API bool Initialize();
		WISHING_API bool Start();
		WISHING_API bool Stop();
		WISHING_API void Finalize();

	private:
		CContentGraph m_graph;
	};
	using CSharedContentSystem = Niflect::TSharedPtr<CContentSystem>;

	class CContentGraphEditingScope
	{
	public:
		CContentGraphEditingScope();
		~CContentGraphEditingScope();
	};

	WISHING_API CSharedContentSystem CreateContentSystem();
}