#include "Engine/Test/TestRegistration.h"
#include "Niflect/NiflectRegistration.h"
#include "Engine/BuiltinAccessor.h"
#include "Engine/Engine.h"
#include "Niflect/Memory/Default/DefaultMemory.h"
#include "Niflect/Serialization/JsonFormat.h"

namespace Niflect
{
	template <typename TAccessor>
	static CSharedAccessor CreateFieldLayout()
	{
		return MakeShared<TAccessor>();
	}
	template <typename TType, typename TAccessor, typename TInfo>
	static TInfo* GetOrRegisterType(CNiflectTable* table, const Niflect::CString& typeName)
	{
		if (!TInternalRegisteredType<TType>::IsValid())
		{
			ASSERT(!typeName.empty());
			table->RegisterType<TInfo, TType>(typeName, &CreateFieldLayout<TAccessor>, typeid(TType).hash_code());
		}
		return Niflect::StaticGetType<TType>();
	}
}

namespace TestRegistration
{
	using namespace Engine;

	void TestTypeNatimeta()
	{
		using namespace Niflect;

		if (false)
		{
			CDefaultMemoryStatsScope scope;
			auto memTest = GetDefaultMemoryStats();

			CNiflectTable table;
			auto type = GetOrRegisterType<float, CFloatAccessor, CNiflectType>(&table, "float");
			auto layout = type->CreateFieldLayout();
			auto sharedSrcData = type->MakeSharedInstance<float>();
			auto& srcData = *sharedSrcData;
			srcData = 1.23f;

			CRwNode rw;
			layout->SaveToRwNode(&srcData, &rw);
			CStringStream ss;
			CJsonFormat::Write(&rw, ss);

			auto sharedDstData = type->MakeSharedInstance<void*>();
			auto& dstData = *reinterpret_cast<float*>(sharedDstData.Get());
			layout->LoadFromRwNode(&dstData, &rw);

			ASSERT(srcData == dstData);

			printf("%f\n", dstData);
			printf("");
		}
		if (false)
		{
			CDefaultMemoryStatsScope scope;
			auto memTest = GetDefaultMemoryStats();

			CNiflectTable table;
			auto type = GetOrRegisterType<Niflect::TArrayNif<float>, TStlArrayAccessor<Niflect::TArrayNif<float> >, CNiflectType>(&table, "Niflect::TArrayNif<float>");
			auto layout = type->CreateFieldLayout();
			{
				auto type = GetOrRegisterType<float, CFloatAccessor, CNiflectType>(&table, "float");
				auto elemLayout = type->CreateFieldLayout();
				layout->AddChild(elemLayout);
			}
			auto sharedSrcData = type->MakeSharedInstance<void*>();
			auto& srcData = *reinterpret_cast<Niflect::TArrayNif<float>*>(sharedSrcData.Get());
			for (uint32 idx = 0; idx < 123; ++idx)
				srcData.push_back(static_cast<float>(idx));

			CRwNode rw;
			layout->SaveToRwNode(&srcData, &rw);
			CStringStream ss;
			CJsonFormat::Write(&rw, ss);

			auto sharedDstData = type->MakeSharedInstance<void*>();
			auto& dstData = *reinterpret_cast<Niflect::TArrayNif<float>*>(sharedDstData.Get());
			layout->LoadFromRwNode(&dstData, &rw);

			ASSERT(srcData == dstData);

			printf("cnt: %u\n", static_cast<uint32>(dstData.size()));
			for (auto& it : dstData)
				printf("%f\n", it);
			printf("");
		}
		if (true)
		{

		}
	}
	void TestRuntimeReg()
	{

	}
}