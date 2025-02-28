#pragma once
#include "Niflect/CommonlyUsed/DefaultAccessorSetting.h"
#include "WishingEngine/Base/PointerAccessor.h"

using namespace NiflectAccessorSetting;

template<typename TInstance, typename T>
NIF_AS_E() TSetting<Wishing::TSharedPtrAccessor<TInstance>, Niflect::TSharedPtr<T> >;