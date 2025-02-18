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

	class CRawTestResourcePtrPtrAccessor : public Niflect::CAccessor
	{
		using MyPtr = CTestResource**;
	protected:
		virtual bool SaveInstanceImpl(const AddrType base, CRwNode* rw) const override
		{
			const auto& instance = *static_cast<const MyPtr*>(base);
			AddRwString(rw, "Path", (*instance)->m_path);
			return true;
		}
		virtual bool LoadInstanceImpl(AddrType base, const CRwNode* rw) const override
		{
			auto& instance = *static_cast<MyPtr*>(base);
			auto path = FindRwString(rw, "Path");
			instance = GetTestResourceFactory()->FindOrAddRawPtrPtr(path);
			return true;
		}
	};

	template <typename TInstanceType>
	class TSharedInstanceAccessor : public Niflect::CAccessor
	{
		using TSharedType = Niflect::TSharedPtr<TInstanceType>;
	protected:
		virtual bool SaveInstanceImpl(const AddrType base, CRwNode* rw) const override
		{
			auto type = Niflect::StaticGetType<TInstanceType>();
			const auto& instance = *static_cast<const TSharedType*>(base);
			if (instance == NULL)
			{
				auto offset = Niflect::GetFieldOffset(&CTestBase1::m_shared_self_instance_4);
				auto dummy = static_cast<const char*>(base) - offset;
				auto owner = reinterpret_cast<const CTestBase1*>(dummy);
				ASSERT(owner->m_base_string_0 == TESTBASE1_SELF_INSTANCE_IDENTIFIER);
				AddRwBool(rw, "IsNULL", true);
				return true;
			}
			return type->SaveInstanceToRwNode(instance.Get(), rw);
		}
		virtual bool LoadInstanceImpl(AddrType base, const CRwNode* rw) const override
		{
			auto type = Niflect::StaticGetType<TInstanceType>();
			auto& instance = *static_cast<TSharedType*>(base);
			bool isNULL = FindRwNode(rw, "IsNULL");
			if (isNULL)
			{
				auto offset = Niflect::GetFieldOffset(&CTestBase1::m_shared_self_instance_4);
				auto dummy = static_cast<const char*>(base) - offset;
				auto owner = reinterpret_cast<const CTestBase1*>(dummy);
				ASSERT(owner->m_base_string_0 == TESTBASE1_SELF_INSTANCE_IDENTIFIER);
				instance = NULL;
				return true;
			}
			instance = Niflect::MakeShared<TInstanceType>();
			return type->LoadInstanceFromRwNode(instance.Get(), rw);
		}
	};
}