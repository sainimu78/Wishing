#include "Niflect/NiflectAccessorSetting.h"
#include "Engine/BuiltinAccessor.h"
#include "Engine/Test/TestMyTransform.h"

namespace EngineTypeBindingSettingScope
{
	using namespace NiflectAccessorSetting;
	using namespace Niflect;
	using namespace Engine;

	NIF_AS_A() TSetting<CBoolAccessor, bool>;
	NIF_AS_A() TSetting<CFloatAccessor, float>;
	NIF_AS_A() TSetting<CStringAccessor, Niflect::CString>;
	NIF_AS_A() TSetting<CStdStringAccessor, std::string>;
	template <typename TInstance, typename T>
	NIF_AS_A() TSetting<TStlArrayAccessor<TInstance>, Niflect::TArrayNif<T> >;
	NIF_AS_A() TSetting<CBitsArrayAccessor, Niflect::TArrayNif<bool> >;
	template <typename TInstance, typename T0, typename T1>
	NIF_AS_A() TSetting<TStlMapAccessor<TInstance>, Niflect::TMap<T0, T1>, std::pair<T0, T1> >;
	template <typename T0, typename T1>
	NIF_AS_A() TSetting<CCompoundAccessor, std::pair<T0, T1> >;
	NIF_AS_A() TSetting<CBitsArrayAccessor, std::vector<bool> >;
	template <typename TInstance, typename T>
	NIF_AS_A() TSetting<TStlArrayAccessor<TInstance>, std::vector<T> >;
	NIF_AS_A() TSetting<TBasicTypeAccessor<int32>, int32>;
	NIF_AS_A() TSetting<TestAccessor2::TMyTransformAccessor<float>, TestAccessor2::TMyTransform<float> >;
	//template <typename T0>
	//NIF_AS_A() TSetting<CCompoundAccessor, TestAccessor2::TMyTransform<T0> >;
}