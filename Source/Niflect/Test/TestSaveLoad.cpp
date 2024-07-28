#include "Niflect/Serialization/Tree/JsonTreeReadWrite2.h"
#include "Niflect/Memory/Stats/NiflectMemoryStats.h"
#include "Niflect/Test/MyField.h"
#include "Niflect/Test/MyClass.h"
#include "Niflect/Field/CompoundField.h"
#include "Niflect/Field/ArrayField.h"
#include "Niflect/Field/MapField.h"
#include "Niflect/Test/TestModule0.h"
#include "Niflect/Test/MyTransformField.h"

static void DebugCopyInstance(void* src, void* dst, const Niflect::TArrayNif<Niflect::CField*>& vecField)
{
	using namespace Niflect;
	CString savedData;
	{
		auto& base = src;

		CRwJson::SizeType poolCapa = 0;//Pool的块内存
		CRwJson::SizeType stackCapa = 0;//Json节点或称Object的预留内存
		//CRwJson::AllocatorStack stack;
		//CRwJson::AllocatorPool allocator(poolCapa, &stack);
		CRwJson::AllocatorStack stack;
		auto& allocator = stack;
		CRwJson::Document jd(&allocator, poolCapa, &allocator);
		auto& joRoot = CRwJson::AsRoot(jd);
		CJsonRwDocument doc(jd, joRoot);
		auto rwRoot = doc.GetRootNode();
		for (auto& it : vecField)
			it->SaveToRwNode(base, rwRoot);
		CRwJson::StringBuffer buffer(&allocator, poolCapa);
		CRwJson::WriteToBuffer(joRoot, buffer);
		//printf("%s\n", buffer.GetString());
		savedData = buffer.GetString();
	}
	{
		auto& base = dst;
		using namespace Niflect;
		CRwJson::SizeType poolCapa = 0;//Pool的块内存
		CRwJson::SizeType stackCapa = 0;//Json节点或称Object的预留内存
		//CRwJson::AllocatorStack stack;
		//CRwJson::AllocatorPool allocator(poolCapa, &stack);
		CRwJson::AllocatorStack stack;
		auto& allocator = stack;
		CRwJson::Document jd(&allocator, poolCapa, &allocator);
		auto& joRoot = CRwJson::ReadFromBuffer(jd, savedData.c_str());
		CJsonRwDocument doc(jd, joRoot);
		auto rwRoot = doc.GetRootNode();
		for (auto& it : vecField)
			it->LoadFromRwNode(base, rwRoot);
		CRwJson::StringBuffer buffer(&allocator, poolCapa);
		CRwJson::WriteToBuffer(joRoot, buffer);

		{
			CRwJson::SizeType poolCapa = 0;//Pool的块内存
			CRwJson::SizeType stackCapa = 0;//Json节点或称Object的预留内存
			//CRwJson::AllocatorStack stack;
			//CRwJson::AllocatorPool allocator(poolCapa, &stack);
			CRwJson::AllocatorStack stack;
			auto& allocator = stack;
			CRwJson::Document jd(&allocator, poolCapa, &allocator);
			auto& joRoot = CRwJson::AsRoot(jd);
			CJsonRwDocument doc(jd, joRoot);
			auto rwRoot = doc.GetRootNode();
			for (auto& it : vecField)
				it->SaveToRwNode(base, rwRoot);
			CRwJson::StringBuffer buffer(&allocator, poolCapa);
			CRwJson::WriteToBuffer(joRoot, buffer);
			printf("%s\n", buffer.GetString());
		}
	}
}
static void DebugCopyInstance2(void* src, void* dst, Niflect::CField* field)
{
	Niflect::TArrayNif<Niflect::CField*> vecField;
	vecField.push_back(field);
	DebugCopyInstance(src, dst, vecField);
}
static void TestSingleBuiltInType()
{
	using namespace MyTestClassScope;
	using namespace Niflect;
	
	auto shared0 = CreateField<CFloatField, CFloatField>();
	auto field0 = shared0.Get();
	
	float srcData = 123.0f;
	float dstData;
	DebugCopyInstance2(&srcData, &dstData, field0);
}
static void TestSimpleClass()
{
	using namespace MyTestClassScope;
	using namespace Niflect;

	auto type = StaticGetType<CMyClass0>();
	auto shared0 = type->CreateFieldLayout();
	auto field0 = shared0.Get();

	CMyClass0 srcData;
	srcData.m_float_0 = 1.23f;
	srcData.m_float_1 = 4.56f;
	CMyClass0 dstData;
	DebugCopyInstance2(&srcData, &dstData, field0);
}
static void TestDefaultArray()
{
	using namespace MyTestClassScope;
	using namespace Niflect;
	
	auto shared0 = CreateField<CArrayField, TArrayNif<float> >();
	auto field0 = shared0.Get();
	{
		auto shared1 = CreateField<CFloatField, CFloatField>();
		auto field1 = shared1.Get();
		field1->InitMemberMeta("reserved_dim0", CAddrOffset::None, field0);
		field0->AddChild(shared1);
	}

	TArrayNif<float> srcData;
	srcData.push_back(1.0f);
	srcData.push_back(2.0f);
	TArrayNif<float> dstData;
	DebugCopyInstance2(&srcData, &dstData, field0);
}
static void TestTypicalClass()
{
	using namespace MyTestClassScope;
	using namespace Niflect;
	
	TArrayNif<CField*> vecField;
	auto baseType = StaticGetType<CMyClassBase0>();
	auto derivedType = StaticGetType<CMyClass1>();
	auto baseField = baseType->GetRootField();
	auto derivedField = derivedType->GetRootField();
	vecField.push_back(baseField);
	vecField.push_back(derivedField);

	CMyClass1 srcData;
	TestInit_CMyClass1(srcData);
	CMyClass1 dstData;
	DebugCopyInstance(&srcData, &dstData, vecField);
}
static void TestCustomField()
{
	using namespace MyTestClassScope;
	using namespace Niflect;
	
	auto shared0 = CreateField<TMyTransformField<float>, TMyTransform<float> >();
	auto field0 = shared0.Get();

	TMyTransform<float> srcData;
	TestInit_TMyTransform(srcData);
	TMyTransform<float> dstData;
	DebugCopyInstance2(&srcData, &dstData, field0);
}
static void TestPair()
{
	using namespace MyTestClassScope;
	using namespace Niflect;
	//
	auto shared0 = MakeShared<CCompoundField>();
	auto field0 = shared0.Get();
	{
		auto shared1 = Niflect::MakeShared<CStringField>();
		auto field1 = shared1.Get();
		field1->InitMemberMeta("first", GetMemberVariableOffset(&std::pair<CString, float>::first), field0);
		field0->AddChild(shared1);
	}
	{
		auto shared1 = Niflect::MakeShared<CFloatField>();
		auto field1 = shared1.Get();
		field1->InitMemberMeta("second", GetMemberVariableOffset(&std::pair<CString, float>::second), field0);
		field0->AddChild(shared1);
	}

	std::pair<CString, float> srcData;
	srcData.first = "Nihao";
	srcData.second = 1.0f;
	std::pair<CString, float> dstData;
	DebugCopyInstance2(&srcData, &dstData, field0);
}

static void MyExp()
{
	auto memTest = Niflect::DebugGetMemoryStats();
	TestCreateModuleReg0();
	//TestSimpleClass();
	//TestDefaultArray();
	TestTypicalClass();
	//TestCustomField();
	//TestDefaultMap();
	//TestPair();
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