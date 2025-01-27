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
		CContentDirNode* AddDirNode(CContentDirNode* parentNode, const Niflect::CString& name, CContentEditContext& ctx);
		CContentFileNode* AddFileNode(CContentDirNode* parentNode, const Niflect::CString& name, CContentEditContext& ctx);
		void DeleteNode(CContentNode* node, CContentEditContext& ctx);
		CContentFileNode* FindOrCreateFileNodePath(const Niflect::CString& filePath, CContentEditContext& ctx);

	//private:
	//	CContentDirNode* FindDirNode(CContentDirNode* parent, const Niflect::CString& name) const;

	private:
		Niflect::TArray<CSharedContentNode> m_vecNode;
		CContentDirNode m_rootDirNode;
	};
}