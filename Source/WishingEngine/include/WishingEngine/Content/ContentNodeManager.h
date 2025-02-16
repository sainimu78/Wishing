#pragma once
#include "WishingEngine/Pipeline/BaseObject.h"
#include "Niflect/Base/Array.h"
#include "WishingEngine/Content/ContentNode.h"
#include "Niflect/Serialization/RwTree.h"

namespace Wishing
{
	using namespace RwTree;

	class CContentNodeManager : public CBaseObject
	{
		typedef CBaseObject inherited;
	public:
		bool Save(CRwNode* rw) const;
		bool Load(const CRwNode* rw);

	private:
		Niflect::TArray<CSharedContentFileNode2> m_vecFileNode;
		Niflect::TArray<CSharedContentDirNode2> m_vecDirNode;
	};
}