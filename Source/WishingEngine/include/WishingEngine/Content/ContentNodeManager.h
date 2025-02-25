#pragma once
#include "WishingEngine/Content/ContentObject.h"
#include "Niflect/Base/Array.h"
#include "WishingEngine/Content/ContentNode.h"
#include "WishingEngine/Content/ContentNodeManager_gen.h"

namespace Wishing
{
	NIF_T()
	class CContentNodeManager : public CContentObject
	{
		CONTENT_OBJECT_DECLARE()
		typedef CContentObject inherited;
	private:
		Niflect::TArray<CSharedContentFileNode2> m_vecFileNode;
		Niflect::TArray<CSharedContentDirNode2> m_vecDirNode;
	};
}