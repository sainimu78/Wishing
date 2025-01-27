#pragma once
#include "Content/ContentDirNode.h"

namespace Wishing
{
	class CContentEditContext
	{
	public:
		void MarkExistingDirty(CContentNode* node) { m_vecExistingDirtyNode.push_back(node); }
		void MarkDeletingDirty(const CSharedContentNode& shared) { m_vecDeletingDirtyNode.push_back(shared); }
		Niflect::TArray<CContentNode*> m_vecExistingDirtyNode;
		Niflect::TArray<CSharedContentNode> m_vecDeletingDirtyNode;
	};

	class CContentManager
	{
	public:
		CContentDirNode* GetRootDirNode();

	public:
		CContentDirNode* InsertDirNode(const Niflect::CString& name, CContentDirNode* parentNode, CContentEditContext& ctx);
		CContentFileNode* InsertFileNode(const Niflect::CString& name, CContentDirNode* parentNode, CContentEditContext& ctx);
		void DeleteNode(CContentNode* node, CContentEditContext& ctx);
		void CreateFileNodePath(const Niflect::CString& filePath, CContentEditContext& ctx);

	private:
		Niflect::TArray<CSharedContentNode> m_vecNode;
		CContentDirNode m_rootDirNode;
	};
}