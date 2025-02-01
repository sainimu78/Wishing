#pragma once
#include "TestModule1Common.h"
#include "TestModule1/TestResource.h"
#include "Niflect/Base/Map.h"
#include "Niflect/Base/String.h"

namespace TestModule1
{
	class CTestResourceFactory
	{
	public:
		CTestResource* FindOrAdd(const Niflect::CString& path)
		{
			CSharedTestResource resource;
			auto ret = m_mapPathToResource.insert({ path, NULL });
			if (ret.second)
			{
				resource = Niflect::MakeShared<CTestResource>();
				resource->InitForTest(path);
				ret.first->second = resource;
			}
			else
			{
				resource = ret.first->second;
			}
			return resource.Get();
		}

	private:
		Niflect::TMap<Niflect::CString, CSharedTestResource> m_mapPathToResource;
	};

	TESTMODULE1_API void CreateTestResourceFactory();
	TESTMODULE1_API void DestroyTestResourceFactory();
	TESTMODULE1_API CTestResourceFactory* GetTestResourceFactory();
}