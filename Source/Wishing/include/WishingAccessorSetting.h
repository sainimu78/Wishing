#pragma once
#include "Niflect/Default/DefaultAccessorSetting.h"
#include "Wishing/Accessor/SharedPtrTypeAccessor.h"

using namespace NiflectAccessorSetting;

template<typename TInstance, typename T>
NIFAS_A() TSetting<Wishing::TSharedPtrTypeSpecialized<TInstance>, Niflect::TSharedPtr<T> >;