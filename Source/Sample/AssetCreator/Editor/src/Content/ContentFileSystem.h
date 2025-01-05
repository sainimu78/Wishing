#pragma once
#include "Content/ContentNode.h"

namespace Wishing
{
	class CContentFileSystem
	{
	public:
		CContentNode* GetRootNode();

	public:
		bool InsertNode(const CSharedContentNode& node, uint32 idx);
		void DeleteNode(uint32 idx);

	private:
		Niflect::TArrayNif<CSharedContentNode> m_vecContentNode;
		CContentNode m_rootNode;
	};
}