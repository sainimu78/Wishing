#pragma once
#include "Content/ContentDirNode.h"
#include "Niflect/Serialization/RwTree.h"

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

	public:
		bool Save(RwTree::CRwNode* rw) const;
		bool Load(const RwTree::CRwNode* rw);

	private:
		Niflect::TArray<CSharedContentNode> m_vecNode;
		CContentDirNode m_rootDirNode;
	};
}