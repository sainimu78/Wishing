#include <stdio.h>
#include "Engine/Engine.h"
//#include "Windows.h"
#include "Niflect/Memory/Default/DefaultMemory.h"

typedef void (*FuncTestAPI_C)();

int main(int argc, char** argv)
{
	TestAPI_Cpp();
	
	using namespace Niflect;

	auto mem = Niflect::CMemory::Alloc(10);
	Niflect::CMemory::Free(mem);

	//auto hLib = LoadLibrary("Engine.dll");
	//if (hLib != NULL)
	//{
	//	if (auto Func = reinterpret_cast<FuncTestAPI_C>(GetProcAddress(hLib, "TestAPI_C")))
	//		Func();
	//}

	printf("Finished\n");
	fflush(stdout);
	return 0;
}