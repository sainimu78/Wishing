#pragma once
#include "Niflect/Base/NiflectMacro.h"
#include "Niflect/Type/RegisteredType.h"

namespace MyTestClassScope
{
	class CMyClass0;
	class CMyClassBase0;
	class CMyClass1;
	//template <typename T>
	//class TMyTransform;
	////using CMyTransform = TMyTransform<float>;
}

namespace Niflect
{
	template <>
	CNiflectType* StaticGetType<MyTestClassScope::CMyClass0>()
	{
		return TInternalRegisteredType<MyTestClassScope::CMyClass0>::s_type;
	}
	template <>
	CNiflectType* StaticGetType<MyTestClassScope::CMyClassBase0>()
	{
		return TInternalRegisteredType<MyTestClassScope::CMyClassBase0>::s_type;
	}
	//template <>
	//CNiflectType* StaticGetType<MyTestClassScope::TMyTransform<float> >()
	//{
	//	return TInternalRegisteredType<MyTestClassScope::TMyTransform<float> >::s_type;
	//}
	template <>
	CNiflectType* StaticGetType<MyTestClassScope::CMyClass1>()
	{
		return TInternalRegisteredType<MyTestClassScope::CMyClass1>::s_type;
	}
	//template <>
	//CNiflectType* StaticGetType<MyTestClassScope::CMyClass0::CMySub0>()
	//{
	//	return TInternalRegisteredType<MyTestClassScope::CMyClass0::CMySub0>::s_type;
	//}
}

#define CURRENT_FILE_ID_55_GENERATED_BODY \
	friend class CMyClass0;

#define CURRENT_FILE_ID_73_GENERATED_BODY \
	friend class CMyClassBase0;

#define CURRENT_FILE_ID_94_GENERATED_BODY \
	friend class CMyClass1;

#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)
#define GENERATED_BODY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY)