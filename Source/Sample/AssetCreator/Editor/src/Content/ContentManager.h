#pragma once
#include "Content/ContentNode.h"

namespace Wishing
{
	class CContentManager
	{
	public:
		CContentNode* GetRootNode();

	public:
		bool InsertNode(const CSharedContentNode& node, uint32 idx);
		void DeleteNode(uint32 idx);

	private:
		Niflect::TArray<CSharedContentNode> m_vecContentNode;
		Niflect::TArray<CContentNode*> m_vecDirtyNode;
		CContentNode m_rootNode;
	};
}