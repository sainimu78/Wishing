#pragma once
#include "Niflect/NiflectAccessorSetting.h"
#include "Accessor/CompoundAccessor.h"
#include "Accessor/ValueTypeAccessor.h"

using namespace NiflectAccessorSetting;

NIFAS_B() TSetting<CCompoundAccessor>;
NIFAS_A() TSetting<CFloatAccessor, float>;