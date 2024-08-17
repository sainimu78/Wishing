#pragma once
#include "NiflectGen/TaggedType/TaggedInheritableType.h"

namespace NiflectGen
{
	class CTaggedClass : public CTaggedInheritableType
	{
		typedef CTaggedInheritableType inherited;
	public:
		CTaggedClass();

	public:
		virtual bool CollectSibling(const CXCursor& cursor, const STaggedNodeCollectingContext& context) override;

	private:
		enum class EStage
		{
			None,
			FoundMember,
		};
		EStage m_stage;
		CXSourceLocation m_tagLocation;
		CX_CXXAccessSpecifier m_lastAccessSpecifier;
	};
}