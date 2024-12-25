#pragma once
#include "Content/ContentNode.h"

namespace Wishing
{
	class CContentFileSystem
	{
	public:
		CContentNode* InsertNode(CContentNode* parent, const Niflect::CString& name, bool isDir);
		void DeleteNode(CContentNode* node);

	private:
		Niflect::TArrayNif<CSharedContentNode> m_vecContentNode;
		CContentNode m_rootNode;
	};
}