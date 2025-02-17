#pragma once
#include "Niflect/Serialization/RwTree.h"

namespace Wishing
{
	using namespace RwTree;

	class CBaseObject
	{
	protected:
		virtual bool Save(CRwNode* rw) const = 0;
		virtual bool Load(const CRwNode* rw) = 0;
	};
}