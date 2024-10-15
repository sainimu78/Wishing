#include "NiflectGen/Collector/UntaggedTemplateMapping.h"
#include "NiflectGen/TaggedType/TaggedType.h"

namespace NiflectGen
{
	void CUntaggedTemplatesMapping::Resolve(const CAliasChain& aliasChain)
	{
		for (auto& it : m_vecType)
			it->ResolveForAlias(aliasChain, *this);
	}
}