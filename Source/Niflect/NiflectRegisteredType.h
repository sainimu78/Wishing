#pragma once
#include "Niflect/NiflectCommon.h"

namespace Niflect
{
	class CNiflectType;

	template <typename T>
	class TInternalRegisteredType
	{
		template <typename T2>
		friend CNiflectType* StaticGetType();
		friend class CNiflectTable;

	public:
		static bool IsValid()
		{
			return s_type != NULL;
		}

	private:
		static CNiflectType* s_type;
	};

	template <typename T>
	CNiflectType* TInternalRegisteredType<T>::s_type = NULL;

	template <typename T>
	extern CNiflectType* StaticGetType();

	template <typename T>
	CNiflectType* StaticGetType()
	{
		return TInternalRegisteredType<T>::s_type;
	}
}