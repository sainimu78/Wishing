#include "Niflect/NiflectBindingSetting.h"
#include "Engine/BuiltinAccessor.h"
#include "Engine/Test/TestMyTransform.h"
#include "NiflectGen/Test/TestOriginalRequiredHeader.h"

namespace EngineTypeBindingSettingScope
{
	using namespace Niflect;

	template <typename TInstance, typename T>
	NIF_BS() TBindingSetting<Engine::TStlArrayAccessor<TInstance>, MyTestType::TMyArray<T> >;
	NIF_BS() TBindingSetting<Engine::CFloatAccessor, float>;
	NIF_BS() TBindingSetting<Engine::CStringAccessor, CString>;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, TestAccessor2::TMyTransform<float> >;
	NIF_BS() TBindingSetting<Engine::CStdStringAccessor, std::string>;
}