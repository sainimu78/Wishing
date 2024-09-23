#include "Niflect/NiflectBindingSetting.h"
#include "Engine/BuiltinAccessor.h"
#include "Engine/Test/TestMyTransform.h"

namespace TestAccessor2
{
	using DDDDDDDDDDD = Niflect::CAccessor;
	using SSSSS = DDDDDDDDDDD;

	template <typename T>
	class TMSSSSSSSSSSSSSSSSS : public SSSSS
	{

	};
}

namespace EngineTypeBindingSettingScope
{
	using namespace Niflect;

	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<float>, TestAccessor2::TMyTransform<float> >;
	using CNihao = TestAccessor2::TMyTransformAccessor<float>;
	NIF_BS() TBindingSetting<CNihao, TestAccessor2::TMyTransform<float> >;
	template <typename T>
	NIF_BS() TBindingSetting<TestAccessor2::TMyTransformAccessor<T>, TestAccessor2::TMyTransform<float> >;
	template <typename T>
	using TMyAccessorAlias = TestAccessor2::TMSSSSSSSSSSSSSSSSS<T>;
	template <typename T>
	NIF_BS() TBindingSetting<TMyAccessorAlias<T>, TestAccessor2::TMyTransform<float> >;

	template <typename T0, typename T1>
	class TSomeBinaryType
	{
	};
	template <typename T0, typename T1>
	class TSomeBinaryTypeAccessor : public Niflect::CAccessor
	{
	};
	template <typename T>
	using TPartiallySpecializedAlias = TSomeBinaryTypeAccessor<float, T>;

	template <typename T>
	NIF_BS() TBindingSetting<TSomeBinaryTypeAccessor<float, T>, TSomeBinaryType<float, T> >;
	template <typename T>
	NIF_BS() TBindingSetting<TPartiallySpecializedAlias<T>, TSomeBinaryType<float, bool> >;
}