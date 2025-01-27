#pragma once
#include "Content/ContentNode.h"

namespace Wishing
{
	class CContentFileNode : public CContentNode
	{
	public:
		static CContentFileNode* Cast(CContentNode* base)
		{
			ASSERT(dynamic_cast<CContentFileNode*>(base) != NULL);
			return static_cast<CContentFileNode*>(base);
		}
		static CContentFileNode* CastChecked(CContentNode* base)
		{
			return dynamic_cast<CContentFileNode*>(base);
		}
	};
}