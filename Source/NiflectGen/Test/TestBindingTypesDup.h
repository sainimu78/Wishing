#include "Niflect/NiflectBindingSetting.h"
#include "Engine/BuiltinAccessor.h"
#include "Engine/Test/TestMyTransform.h"

namespace EngineTypeBindingSettingScope
{
	using namespace Niflect;

	using CMyTM = TestAccessor2::TMyTransform<float>;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, TestAccessor2::TMyTransform<float> >;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, TestAccessor2::TMyTransform<float> >;//failed
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, float>;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, float>;//failed
	using CMyFloat = float;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, CMyFloat>;
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, CMyFloat>;//failed
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
	template <typename T>
	using TPartiallySpecializedAlias = TSomeBinaryTypeAccessor<float, T>;
	template <typename T>
	NIF_BS() TBindingSetting<TPartiallySpecializedAlias<T>, TSomeBinaryType<float, T> >;//failed, 不支持部分特化的模板
}