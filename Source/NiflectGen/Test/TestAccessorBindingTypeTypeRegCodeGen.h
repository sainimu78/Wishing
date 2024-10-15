#include "Niflect/NiflectBindingSetting.h"
#include "Engine/BuiltinAccessor.h"
#include "Engine/Test/TestMyTransform.h"
#include "NiflectGen/Test/TestSomeTypes.h"

namespace EngineTypeBindingSettingScope
{
	using namespace Niflect;
	using namespace Engine;

	NIF_BS() TBindingSetting<CBoolAccessor, bool>;
	NIF_BS() TBindingSetting<CFloatAccessor, float>;
	NIF_BS() TBindingSetting<CStringAccessor, Niflect::CString>;
	NIF_BS() TBindingSetting<CStdStringAccessor, std::string>;
	template <typename TInstance, typename T>
	NIF_BS() TBindingSetting<TStlArrayAccessor<TInstance>, Niflect::TArrayNif<T> >;
	NIF_BS() TBindingSetting<CBitsArrayAccessor, Niflect::TArrayNif<bool> >;
	template <typename TInstance, typename T0, typename T1>
	NIF_BS() TBindingSetting<TStlMapAccessor<TInstance>, Niflect::TMap<T0, T1>, std::pair<T0, T1> >;
	template <typename T0, typename T1>
	NIF_BS() TBindingSetting<CCompoundAccessor, std::pair<T0, T1> >;
	NIF_BS() TBindingSetting<CBitsArrayAccessor, std::vector<bool> >;
	template <typename TInstance, typename T>
	NIF_BS() TBindingSetting<TStlArrayAccessor<TInstance>, std::vector<T> >;
	NIF_BS() TBindingSetting<TBasicTypeAccessor<int32>, int32>;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, TestAccessor2::TMyTransform<float> >;
}