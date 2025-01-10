#pragma once
#include "Content/ContentNode.h"

namespace Wishing
{
	class CContentDirNode : public CContentNode
	{
	public:

	public:
		//static CContentDirNode* Cast(CContentNode* base)
		//{
		//	ASSERT(dynamic_cast<CContentDirNode*>(base) != NULL);
		//	return static_cast<CContentDirNode*>(base);
		//}
		static CContentDirNode* CastChecked(CContentNode* base)
		{
			return dynamic_cast<CContentDirNode*>(base);
		}
	};
}