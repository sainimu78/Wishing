#pragma once
#include "WishingEngineCommon.h"
#include "Niflect/Base/SharedPtr.h"
#include "Niflect/Base/Array.h"
#include "WishingEngine/Content/ContentNode.h"

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

	public:
		CContentDirNode2* GetRootDirNode() const;
		void AddFileNode(const CSharedContentFileNode2& node);
		void AddDirNode(const CSharedContentDirNode2& node);

	private:
		Niflect::TArray<CSharedContentFileNode2> m_vecFileNode;
		Niflect::TArray<CSharedContentDirNode2> m_vecDirNode;
		CSharedContentDirNode2 m_rootDirNode;
	};
	using CSharedContentSystem = Niflect::TSharedPtr<CContentSystem>;

	WISHINGENGINE_API CSharedContentSystem CreateContentSystem();
}