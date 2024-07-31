#include "Niflect/Test/MyField.h"
#include "Niflect/Serialization/Tree/JsonTreeReadWrite2.h"
#include "Niflect/Field/ArrayField.h"
#include "Niflect/Field/CompoundField.h"
#include "Niflect/Test/MyClass.h"
#include "Niflect/Util/DebugUtil.h"
#include "Niflect/Test/TestModule0.h"
#include "Niflect/Test/MyTransformField.h"
#include "Niflect/Memory/Default/DefaultMemory.h"

namespace Niflect
{
	CString DebugSavePropertyString(CProperty* prop);
	void DebugLoadPropertyString(CProperty* prop, const CString& buffer);

	CString DebugSavePropertyString(CProperty* prop)
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
		prop->SaveWithCachedBase(rwRoot);
		CRwJson::StringBuffer stm(&allocator, poolCapa);
		CRwJson::WriteToBuffer(joRoot, stm);
		return stm.GetString();
	}
	void DebugLoadPropertyString(CProperty* prop, const CString& buffer)
	{
		CRwJson::SizeType poolCapa = 0;//Pool的块内存
		CRwJson::SizeType stackCapa = 0;//Json节点或称Object的预留内存
		//CRwJson::AllocatorStack stack;
		//CRwJson::AllocatorPool allocator(poolCapa, &stack);
		CRwJson::AllocatorStack stack;
		auto& allocator = stack;
		CRwJson::Document jd(&allocator, poolCapa, &allocator);
		auto& joRoot = CRwJson::ReadFromBuffer(jd, buffer.data());
		CJsonRwDocument doc(jd, joRoot);
		auto rwRoot = doc.GetRootNode();
		prop->LoadWithCachedBase(rwRoot);
	}

	static void PrintPropertyRecurs(CProperty* parentProp, uint32 level = 0)
	{
		auto strLevel = NiflectUtil::DebugIndentToString(level);
		CString strValue;
		if (parentProp->GetParent() == NULL)
			strValue = "Root";
		else
			strValue = "Not a value";
		if (parentProp->GetChildrenCount() == 0)
		{
			strValue = DebugSavePropertyString(parentProp);
		}
		printf("%s%s, %s\n", strLevel.c_str(), parentProp->GetName().c_str(), strValue.c_str());

		level++;
		for (uint32 idx = 0; idx < parentProp->GetChildrenCount(); ++idx)
			PrintPropertyRecurs(parentProp->GetChild(idx), level);
	}
}

static void TestSimpleClass()
{
	using namespace MyTestClassScope;
	using namespace Niflect;

	auto type = StaticGetType<CMyClass0>();
	auto field0 = type->GetRootField();

	CMyClass0 srcData;
	srcData.m_float_0 = 1.23f;
	srcData.m_float_1 = 4.56f;

	auto rootProp = field0->CreatePropertyTree(&srcData);
	PrintPropertyRecurs(rootProp.Get());
}
static void TestDefaultArray()
{
	using namespace MyTestClassScope;
	using namespace Niflect;
	
	auto shared0 = CreateField<CArrayField, TArrayNif<float> >();
	auto field0 = shared0.Get();
	{
		auto shared1 = Niflect::MakeShared<CFloatField>();
		auto field1 = shared1.Get();
		field1->InitMemberMeta("reserved_dim0", CAddrOffset::None, field0);
		field0->AddChild(shared1);
	}

	TArrayNif<float> srcData;
	srcData.push_back(1.0f);
	srcData.push_back(2.0f);

	auto rootProp = field0->CreatePropertyTree(&srcData);
	PrintPropertyRecurs(rootProp.Get());
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

	auto base = &srcData;
	auto rootProp = MakeShared<CDefaultProperty>();
	for (auto& it : vecField)
	{
		auto childProp = it->CreatePropertyTree(base);
		rootProp->AddChild(childProp);
	}

	PrintPropertyRecurs(rootProp.Get());
}
static void TestCustomField()
{
	using namespace MyTestClassScope;
	using namespace Niflect;

	auto shared0 = MakeShared<TMyTransformField<float> >();
	auto field0 = shared0.Get();

	TMyTransform<float> srcData;
	TestInit_TMyTransform(srcData);
	auto rootProp = field0->CreatePropertyTree(&srcData);
	PrintPropertyRecurs(rootProp.Get());
}

static void MyExp()
{
	auto memTest = Niflect::GetDefaultMemoryStats();
	TestCreateModuleReg0();
	TestTypicalClass();
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