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

		{
			CDefaultMemoryStatsScope scope;
			auto memTest = GetDefaultMemoryStats();

			//TestCreateModuleReg0();

			//Niflect::StaticGetType_Misc<float>("float");

			//std::vector<bool> aaa;
			//std::vector<bool>::value_type& a = aaa[0];
			//a = false;

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
			auto& dstData = *sharedDstData;
			layout->LoadFromRwNode(&dstData, &rw);
			auto& instance = *reinterpret_cast<float*>(&dstData);

			printf("%f\n", instance);

			//TestDestroyModuleReg0();
		}
		printf("");
	}
	void TestRuntimeReg()
	{

	}
}