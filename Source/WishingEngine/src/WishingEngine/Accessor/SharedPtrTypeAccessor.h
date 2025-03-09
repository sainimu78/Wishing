#pragma once
#include "Niflect/NiflectAccessor.h"
#include "Niflect/NiflectRegisteredType.h"

namespace Wishing
{
	using namespace RwTree;

	template <typename TPtr>
	class TSharedPtrTypeSpecialized : public Niflect::CAccessor
	{
		using CSharedPtrType = Niflect::TSharedPtr<TPtr>;
	protected:
		virtual bool SaveInstanceImpl(const InstanceType* base, CRwNode* rw) const override
		{
			auto& instance = *static_cast<const CSharedPtrType*>(base);
			if (instance == NULL)
			{
				AddRwBool(rw, "NULL", true);
				return true;
			}
			auto type = Niflect::StaticGetType<TPtr>();
			return type->SaveInstanceToRwNode(instance.Get(), rw);
		}
		virtual bool LoadInstanceImpl(InstanceType* base, const CRwNode* rw) const override
		{
			auto& instance = *static_cast<CSharedPtrType*>(base);
			bool isNULL = FindRwBool(rw, "NULL");
			if (isNULL)
			{
				instance = NULL;
				return true;
			}
			auto type = Niflect::StaticGetType<TPtr>();
			instance = Niflect::MakeShared<TPtr>();
			return type->LoadInstanceFromRwNode(instance.Get(), rw);
		}
	};
}