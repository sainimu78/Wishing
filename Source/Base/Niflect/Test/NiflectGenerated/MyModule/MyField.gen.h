#pragma once
#include "Niflect/Base/NiflectMacro.h"
#include "Niflect/Type/RegisteredType.h"

namespace MyTestClassScope
{
	class CFloatField;
	class CStringField;
	class CBoolField;
}

namespace Niflect
{
	template <>
	CNiflectType* StaticGetType<MyTestClassScope::CFloatField>()
	{
		return TInternalRegisteredType<MyTestClassScope::CFloatField>::s_type;
	}
	template <>
	CNiflectType* StaticGetType<MyTestClassScope::CStringField>()
	{
		return TInternalRegisteredType<MyTestClassScope::CStringField>::s_type;
	}
	template <>
	CNiflectType* StaticGetType<MyTestClassScope::CBoolField>()
	{
		return TInternalRegisteredType<MyTestClassScope::CBoolField>::s_type;
	}
}