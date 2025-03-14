#pragma once
#include "Wishing/WishingObject.h"
#include "Niflect/Base/Array.h"
#include "Wishing/Content/ContentNode.h"
#include "Wishing/Content/ContentGraph_gen.h"

namespace Wishing
{
	NIF_T()
	class CContentGraph : public CWishingObject
	{
		WISHINGOBJECT_DECLARE()
		typedef CWishingObject inherited;
	//public:
	//	bool AddFileNode(const CSharedContentFileNode2& node);
	//	bool AddDirNode(const CSharedContentDirNode2& node);

	private:
		Niflect::TArray<CSharedContentFileNode2> m_vecFileNode;
		Niflect::TArray<CSharedContentDirNode2> m_vecDirNode;
	};
}