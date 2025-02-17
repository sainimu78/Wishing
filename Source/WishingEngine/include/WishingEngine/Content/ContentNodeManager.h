#pragma once
#include "WishingEngine/Pipeline/BaseObject.h"
#include "Niflect/Base/Array.h"
#include "WishingEngine/Content/ContentNode.h"

namespace Wishing
{
	class CContentNodeManager : public CBaseObject
	{
		typedef CBaseObject inherited;
	public:
		virtual bool Save(CRwNode* rw) const override;
		virtual bool Load(const CRwNode* rw) override;

	private:
		Niflect::TArray<CSharedContentFileNode2> m_vecFileNode;
		Niflect::TArray<CSharedContentDirNode2> m_vecDirNode;
	};
}