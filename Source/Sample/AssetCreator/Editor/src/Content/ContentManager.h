#pragma once
#include "Content/ContentDirNode.h"

namespace Wishing
{
	class CContentChangeContext
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
		CContentDirNode* AddDirNode(CContentDirNode* parentNode, const Niflect::CString& name, CContentChangeContext& ctx);
		CContentFileNode* AddFileNode(CContentDirNode* parentNode, const Niflect::CString& name, CContentChangeContext& ctx);
		void DeleteNode(CContentFileNode* node, CContentChangeContext& ctx);
		CContentFileNode* FindOrCreateFileNodePath(const Niflect::CString& filePath, CContentChangeContext& ctx);

	//private:
	//	CContentDirNode* FindDirNode(CContentDirNode* parent, const Niflect::CString& name) const;

	private:
		Niflect::TArray<CSharedContentNode> m_vecNode;
		CContentDirNode m_rootDirNode;
	};
}