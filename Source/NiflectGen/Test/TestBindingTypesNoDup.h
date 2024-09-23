#include "Niflect/NiflectBindingSetting.h"
#include "Engine/BuiltinAccessor.h"
#include "Engine/Test/TestMyTransform.h"

namespace EngineTypeBindingSettingScope
{
	using namespace Niflect;

	using CMyTM = TestAccessor2::TMyTransform<float>;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, TestAccessor2::TMyTransform<float> >;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, CMyTM>;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, TestAccessor2::TMyTransform<double> >;
	using CMyFloat = float;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, float>;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, CMyFloat>;
	using CMyTM2 = TestAccessor2::TMyTransform<CMyFloat>;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, CMyTM2>;
	template <typename T>
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<T>, TestAccessor2::TMyTransform<T> >;
	template <typename T>
	using TMyTM = TestAccessor2::TMyTransform<T>;
	template <typename T>
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<T>, TMyTM<T> >;
	template <typename T0, typename T1>
	class TSomeBinaryType
	{
	};
	template <typename T0, typename T1>
	class TSomeBinaryTypeAccessor : public Niflect::CAccessor
	{
	};
	template <typename T0, typename T1>
	NIF_BS() TBindingSetting<TSomeBinaryTypeAccessor<T0, T1>, TSomeBinaryType<T0, T1> >;
}