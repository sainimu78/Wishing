#pragma once
#include "Content/ContentNode.h"
#include "Content/ContentFileNode.h"

namespace Wishing
{
	class CContentDirNode : public CContentNode
	{
	public:
		void AddChild(CContentNode* node);
		void DeleteChild(CContentNode* node);
		//uint32 FindChildIndex(const Niflect::CString& name) const;
		CContentNode* FindChild(const Niflect::CString& name) const;
		CContentDirNode* FindChildDir(const Niflect::CString& name) const;
		CContentFileNode* FindChildFile(const Niflect::CString& name) const;

	public:
		static CContentDirNode* Cast(CContentNode* base)
		{
			ASSERT(dynamic_cast<CContentDirNode*>(base) != NULL);
			return static_cast<CContentDirNode*>(base);
		}
		static CContentDirNode* CastChecked(CContentNode* base)
		{
			return dynamic_cast<CContentDirNode*>(base);
		}

	private:
		Niflect::TArray<CContentNode*> m_vecChild;
	};
}