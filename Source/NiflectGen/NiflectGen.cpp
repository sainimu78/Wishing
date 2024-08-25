#include "NiflectGen/NiflectGen.h"
#include <stdio.h>
#include <vector>
#include <typeinfo>

void TestFunc()
{
	printf("NiflectGen Test, %llu\n", typeid(std::vector<float>).hash_code());
}