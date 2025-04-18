#pragma once
#include "Niflect/NiflectAccessor.h"
#include "Accessor/CompoundAccessor_gen.h"

using namespace RwTree;

NIF_T()
class CCompoundAccessor : public Niflect::CAccessor
{
protected:
	virtual bool SaveInstanceImpl(const InstanceType* base, CRwNode* rw) const override
	{
		for (auto& it : this->GetFields())
		{
			ASSERT(!it.GetName().empty());
			auto rwField = CreateRwNode();
			if (it.LayoutSaveToRwNode(base, rwField.Get()))
				AddExistingRwNode(rw, it.GetName(), rwField);
		}
		return true;
	}
	virtual bool LoadInstanceImpl(InstanceType* base, const CRwNode* rw) const override
	{
		for (auto& it : this->GetFields())
		{
			ASSERT(!it.GetName().empty());
			auto rwChild = FindRwNode(rw, it.GetName());
			it.LayoutLoadFromRwNode(base, rwChild);
		}
		return true;
	}
};