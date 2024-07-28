#pragma once
#include "Niflect/Base/NiflectMacro.h"
#include "Niflect/Type/RegisteredType.h"

namespace MyTestClassScope
{
	template <typename T>
	class TMyTransform;

	typedef TMyTransform<float> CMyTrasformFloat;
}

namespace Niflect
{
	template <>
	CNiflectType* StaticGetType<MyTestClassScope::CMyTrasformFloat>()
	{
		return TInternalRegisteredType<MyTestClassScope::CMyTrasformFloat>::s_type;
	}
}