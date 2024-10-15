#pragma once
#include "NiflectGen/Util/CursorMap.h"
#include "NiflectGen/Collector/AliasChain.h"

namespace NiflectGen
{
	class CUntaggedTemplate;

	class CUntaggedTemplatesMapping
	{
	public:
		void Init(const CAliasChain& aliasChain);
		TCursorMap<uint32> m_mapCursorToIndex;
		Niflect::TArrayNif<CUntaggedTemplate*> m_vecType;
	};
	using CSharedUntaggedTemplatesMapping = Niflect::TSharedPtr<CUntaggedTemplatesMapping>;
}