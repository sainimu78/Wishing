#pragma once
#include "Niflect/NiflectAccessor.h"
#include "TestModule1/TestResourceFactory.h"

namespace TestModule1
{
	using namespace RwTree;

	class CRawTestResourceAccessor : public Niflect::CAccessor
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
			instance = GetTestResourceFactory()->FindOrAddRaw(path);
			return true;
		}
	};

	template <typename TInstance>
	class TRawTestResourcePointerAccessor : public Niflect::CAccessor
	{
	protected:
		virtual bool SaveInstanceImpl(const AddrType base, CRwNode* rw) const override
		{
			const auto& instance = *static_cast<const TInstance*>(base);
			AddRwString(rw, "Path", instance.m_p->m_path);
			return true;
		}
		virtual bool LoadInstanceImpl(AddrType base, const CRwNode* rw) const override
		{
			auto& instance = *static_cast<TInstance*>(base);
			auto path = FindRwString(rw, "Path");
			instance.m_p = GetTestResourceFactory()->FindOrAddRaw(path);
			return true;
		}
	};

	class CSharedTestResourceAccessor : public Niflect::CAccessor
	{
	protected:
		virtual bool SaveInstanceImpl(const AddrType base, CRwNode* rw) const override
		{
			const auto& instance = *static_cast<const CSharedTestResource*>(base);
			AddRwString(rw, "Path", instance->m_path);
			return true;
		}
		virtual bool LoadInstanceImpl(AddrType base, const CRwNode* rw) const override
		{
			auto& instance = *static_cast<CSharedTestResource*>(base);
			auto path = FindRwString(rw, "Path");
			instance = GetTestResourceFactory()->FindOrAddShared(path);
			return true;
		}
	};
}