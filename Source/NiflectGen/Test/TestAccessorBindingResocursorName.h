#include "Niflect/NiflectBindingSetting.h"
#include "Engine/BuiltinAccessor.h"
#include "Engine/Test/TestMyTransform.h"

namespace MyScope2
{
	template <typename T>
	using TMyScope2TM = TestAccessor2::TMyTransform<T>;

	namespace SubScope1
	{
		template <typename T>
		using TMySubScope1TM = TestAccessor2::TMyTransform<T>;
	}

	struct SMyStruct
	{
		int32 m_int_0;
	};
}

namespace EngineTypeBindingSettingScope
{
	using namespace Niflect;
	using namespace Engine;
	using namespace TestAccessor2;
	using namespace MyScope2;
	using namespace SubScope1;
	using namespace std;

	NIF_BS() TBindingSetting<TMyTransformAccessor<float>, TMyTransform<float> >;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, TMyTransform<double> >;
	NIF_BS() TBindingSetting<TMyTransformAccessor<float>, TMyScope2TM<int32> >;
	NIF_BS() TBindingSetting<TMyTransformAccessor<float>, TMySubScope1TM<uint32> >;
	NIF_BS() TBindingSetting<TMyTransformAccessor<float>, SubScope1::TMySubScope1TM<int64> >;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, TArrayNif<SMyStruct> >;
	template <typename TInstance, typename T>
	NIF_BS() TBindingSetting<TStlArrayAccessor<TInstance>, TArrayNif<T> >;
	template <typename T0, typename T1>
	NIF_BS() TBindingSetting<CCompoundAccessor, pair<T0, T1> >;
}