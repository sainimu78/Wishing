#include "Niflect/NiflectAccessorSetting.h"
#include "Engine/BuiltinAccessor.h"
#include "Engine/Test/TestMyTransform.h"
#include "NiflectGen/Test/TestModuleHeaderRequiredHeader.h"

namespace EngineTypeBindingSettingScope
{
	using namespace NiflectAccessorSetting;
	using namespace Niflect;

	template <typename TInstance, typename T>
	NIF_AS_A() TSetting<Engine::TStlArrayAccessor<TInstance>, MyTestType::TMyArray<T> >;
	NIF_AS_A() TSetting<Engine::CFloatAccessor, float>;
	NIF_AS_A() TSetting<Engine::CStringAccessor, CString>;
	NIF_AS_A() TSetting<TestAccessor2::TMyTransformAccessor<float>, TestAccessor2::TMyTransform<float> >;
	NIF_AS_A() TSetting<Engine::CStdStringAccessor, std::string>;
}