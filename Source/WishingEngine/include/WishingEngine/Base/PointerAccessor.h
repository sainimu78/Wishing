#pragma once
#include "Niflect/NiflectAccessor.h"
#include "Niflect/NiflectModuleManager.h"

namespace Wishing
{
	using namespace RwTree;

	template <typename TSharedType>
	class TSharedPtrAccessor : public Niflect::CAccessor
	{
	protected:
		virtual bool SaveInstanceImpl(const AddrType base, CRwNode* rw) const override
		{
			auto& instance = *static_cast<const TSharedType*>(base);
			if (instance == NULL)
			{
				AddRwBool(rw, "IsNULL", true);
				return true;
			}
			auto type = instance->GetType();
			return type->SaveInstanceToRwNode(instance.Get(), rw);
		}
		virtual bool LoadInstanceImpl(AddrType base, const CRwNode* rw) const override
		{
			auto& instance = *static_cast<TSharedType*>(base);
			bool isNULL = FindRwNode(rw, "IsNULL");
			if (isNULL)
			{
				instance = NULL;
				return true;
			}
			auto type = instance
			instance = Niflect::MakeShared<TInstanceType>();
			return type->LoadInstanceFromRwNode(instance.Get(), rw);
		}
	};
}