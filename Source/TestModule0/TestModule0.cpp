#include "TestModule0/TestModule0.h"
#include "TestModule0/TestModule0.private.h"
#include "Engine/Test/TestRegistration.h"

namespace TestModule0
{
	void LoadTypes()
	{
		auto a = Niflect::StaticGetType<TestRegistration::CMyRegClass>();
		printf("Dependency Type: %s\n", a->GetTypeName().c_str());
	}
	void UnloadTypes()
	{
	}
}