#pragma once
#include "Niflect/NiflectAccessor.h"
#include "Accessor/ValueTypeAccessor_gen.h"

using namespace RwTree;

template <typename TValue>
class TBuiltinTypeAccessor : public Niflect::CAccessor
{
public:
	virtual bool SaveInstanceImpl(const InstanceType* base, CRwNode* rw) const override
	{
		auto& instance = *static_cast<const TValue*>(base);
		ASSERT(!rw->IsValue());
		auto rwValue = rw->ToValue();
		SetRwValueAs<TValue>(rwValue, instance);
		return true;
	}
	virtual bool LoadInstanceImpl(InstanceType* base, const CRwNode* rw) const override
	{
		auto& instance = *static_cast<TValue*>(base);
		ASSERT(rw->IsValue());
		auto rwValue = rw->GetValue();
		instance = GetRwValueAs<TValue>(rwValue);
		return true;
	}
};

//NIF_T()
//class CBoolAccessor : public TBuiltinTypeAccessor<bool>
//{
//};
NIF_T()
class CFloatAccessor : public TBuiltinTypeAccessor<float>
{
};