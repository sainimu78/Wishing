#include "Engine/Test/TestStaticGetType.h"

namespace TestRegistration
{
	void SSSSSSSS()
	{
		auto a = Niflect::StaticGetType<CMyRegClass>();
		auto b = Niflect::StaticGetType<float>();
		printf("%s, %s\n", a->GetTypeName().c_str(), b->GetTypeName().c_str());
	}
}