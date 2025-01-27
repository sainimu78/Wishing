#pragma once
#include "Content/ContentNode.h"
#include "Content/ContentFileNode.h"

namespace Wishing
{
	class CContentDirNode : public CContentNode
	{
	public:
		void AddDirNode(CContentDirNode* node)
		{
			this->AddNodeInternal(m_vecDirNode, node);
		}
		void AddFileNode(CContentFileNode* node)
		{
			this->AddNodeInternal(m_vecFileNode, node);
		}
		void DeleteDirNode(CContentDirNode* node)
		{
			this->DeleteNodeInternal(m_vecDirNode, node);
		}
		void DeleteFileNode(CContentFileNode* node)
		{
			this->DeleteNodeInternal(m_vecFileNode, node);
		}
		CContentDirNode* FindDirNode(const Niflect::CString& name) const
		{
			return this->FindNodeInternal<CContentDirNode>(m_vecDirNode, name);
		}
		CContentFileNode* FindFileNode(const Niflect::CString& name) const
		{
			return this->FindNodeInternal<CContentFileNode>(m_vecFileNode, name);
		}

	public:
		const Niflect::TArray<CContentDirNode*>& GetDirNodes() const { return m_vecDirNode; }
		const Niflect::TArray<CContentFileNode*>& GetFileNodes() const { return m_vecFileNode; }

	private:
		template <typename TNodeArray, typename TNode>
		void AddNodeInternal(TNodeArray& vecNode, TNode* node)
		{
			vecNode.push_back(node);
		}
		template <typename TNodeArray, typename TNode>
		void DeleteNodeInternal(TNodeArray& vecNode, TNode* node)
		{
			auto itFound = std::find(vecNode.begin(), vecNode.end(), node);
			ASSERT(itFound != vecNode.end());
			vecNode.erase(itFound);
		}
		template <typename TNode, typename TNodeArray>
		TNode* FindNodeInternal(TNodeArray& vecNode, const Niflect::CString& name) const
		{
			for (auto& it : vecNode)
			{
				if (it->GetName() == name)
					return it;
			}
			return NULL;
		}

	//public:
	//	static CContentDirNode* Cast(CContentNode* base)
	//	{
	//		ASSERT(dynamic_cast<CContentDirNode*>(base) != NULL);
	//		return static_cast<CContentDirNode*>(base);
	//	}
	//	static CContentDirNode* CastChecked(CContentNode* base)
	//	{
	//		return dynamic_cast<CContentDirNode*>(base);
	//	}

	private:
		Niflect::TArray<CContentFileNode*> m_vecFileNode;
		Niflect::TArray<CContentDirNode*> m_vecDirNode;
	};

	void DebugPrintDirNodeRecurs(const CContentDirNode* parentNode, int level = 0);
}