#include "Niflect/Test/MyField.h"
#include "Niflect/Serialization/Tree/JsonTreeReadWrite2.h"
#include "Niflect/Field/ArrayField.h"
#include "Niflect/Field/CompoundField.h"
#include "Niflect/Test/MyClass.h"
#include "Niflect/Util/DebugUtil.h"
#include "Niflect/Test/TestModule0.h"
#include "Niflect/Util/TypeUtil.h"
#include "Windows.h"
#include "stdio.h"
#include "Niflect/Memory/Default/DefaultMemory.h"

static void MyExp()
{
	using namespace Niflect;

	auto memTest = GetDefaultMemoryStats();
	TestCreateModuleReg0();

	{
		using namespace MyTestClassScope;
		
		auto type = Cast<CClass>(StaticGetType<CMyClassBase0>());
		CMyClassBase0 obj;

		float a = 1.0f;
		CMyClass0 b;
		bool temp0 = true;
		bool* c = &temp0;
		CMyClass0 temp1;
		temp1.m_float_1 = 2.0f;
		CMyClass0* d = &temp1;
		float temp2_0[] = {3.0f, 4.0f, 5.0f, 6.0f};
		float temp2_1[] = {7.0f, 8.0f, 9.0f, 10.0f};
		float temp2_2[] = {11.0f, 12.0f, 13.0f, 14.0f};
		float* temp2[3] = {temp2_0, temp2_1, temp2_2};
		//实验时略有误解, 以下这种定义为连续内存, 访问是通过float*, 而不是float**
		//float temp2[3][4] = {{3.0f, 4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f, 10.0f}, {11.0f, 12.0f, 13.0f, 14.0f}};
		auto e = &temp2;
		void* inputInstanceArray[] = {&a, &b, &c, &d, &e};
		bool ret = false;
		void* outputInstanceArray[] = {&ret};
		type->m_vecMethod[0].Invoke(&obj, inputInstanceArray, outputInstanceArray);
		ASSERT(ret);
		printf("");
	}
	
	TestDestroyModuleReg0();
	printf("");
}

#ifdef TEST_FOR_GCC
#else
#include <Windows.h>
class CStaticTest
{
public:
	CStaticTest()
	{
#ifdef WIN32
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
#endif
		MyExp();
	}
};
//CStaticTest s;
#endif

#ifdef TEST_FOR_GCC
int main()
{
	MyExp();
	return 0;
}
#else
#endif