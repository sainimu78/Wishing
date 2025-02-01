#pragma once
#include "Niflect/NiflectAccessor.h"
#include "TestModule1/TestResourceFactory.h"

namespace TestModule1
{
	using namespace RwTree;

	class CTestResourceAccessor : public Niflect::CAccessor
	{
		using MyPtr = CTestResource*;
	protected:
		virtual bool SaveInstanceImpl(const AddrType base, CRwNode* rw) const override
		{
			const auto& instance = *static_cast<const MyPtr*>(base);
			AddRwString(rw, "Path", instance->m_path);
			return true;
		}
		virtual bool LoadInstanceImpl(AddrType base, const CRwNode* rw) const override
		{
			auto& instance = *static_cast<MyPtr*>(base);
			auto path = FindRwString(rw, "Path");
			instance = GetTestResourceFactory()->FindOrAdd(path);
			return true;
		}
	};
}