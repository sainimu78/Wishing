#include "Content/ContentDirNode.h"
#include "Niflect/Util/DebugUtil.h"

namespace Wishing
{
	static void DebugPrintNode(const CContentNode* node, int level)
	{
		auto strLv = NiflectUtil::DebugIndentToString(level);
		printf("%s%s\n", strLv.c_str(), node->GetName().c_str());
	}

	void DebugPrintDirNodeRecurs(const CContentDirNode* parentNode, int level)
	{
		DebugPrintNode(parentNode, level);

		level++;
		for (auto& it : parentNode->GetFileNodes())
			DebugPrintNode(it, level);
		for (auto& it : parentNode->GetDirNodes())
			DebugPrintDirNodeRecurs(it, level);
	}
}