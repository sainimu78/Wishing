#pragma once
#include "Niflect/NiflectMacro.h"

namespace TestSomeScope
{
	NIF_T()
	enum class EMyEnumClassOption
	{
		EDefaultMode NIF_C(),
		EMode0 NIF_C(),
		EState0 NIF_C(),
	};
}