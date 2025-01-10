#pragma once
#include "Content/ContentNode.h"

namespace Wishing
{
	class CContentFileNode : public CContentNode
	{
	public:
		static CContentFileNode* CastChecked(CContentNode* base)
		{
			return dynamic_cast<CContentFileNode*>(base);
		}
	};
}