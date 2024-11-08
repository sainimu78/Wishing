#pragma once
#include "Niflect/NiflectAccessor.h"

namespace Niflect
{
	class CCompoundAccessor : public CAccessor
	{
	public:
		virtual bool SaveInstanceImpl(const AddrType base, CRwNode* rw) const override
		{
			auto count = this->GetChildrenCount();
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto childAccessor = this->GetChild(idx);
				ASSERT(!childAccessor->GetName().empty());
				auto rwChild = CreateRwNode();
				if (childAccessor->SaveToRwNode(base, rwChild.Get()))
					AddExistingRwNode(rw, childAccessor->GetName(), rwChild);
			}
			return true;
		}
		virtual bool LoadInstanceImpl(AddrType base, const CRwNode* rw) const override
		{
			auto count = this->GetChildrenCount();
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto childAccessor = this->GetChild(idx);
				ASSERT(!childAccessor->GetName().empty());
				auto rwChild = FindRwNode(rw, childAccessor->GetName());
				childAccessor->LoadFromRwNode(base, rwChild);
			}
			return true;
		}
	};
}