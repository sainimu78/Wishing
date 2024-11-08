#pragma once
#include "Niflect/CommonlyUsed/ContainerTypeAccessor.h"

namespace Niflect
{
	template <typename TArrayType>
	using TSTLArrayAccessor = TArrayAccessor<TArrayType>;

	template <typename TBitsArrayType>
	using TSTLBitsArrayAccessor = TBitsArrayAccessor<TBitsArrayType>;

	template <typename TMapType>
	using TSTLMapAccessor = TMapAccessor<TMapType>;
}