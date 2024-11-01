#pragma once
#include "Niflect/NiflectBase.h"

namespace NiflectGen
{
	using CCodeLines = Niflect::TArrayNif<Niflect::CString>;
	
	namespace EscapeChar
	{
		static const char* NewLine = "\n";
	}

	class CWritingHeaderSearchPaths
	{
	public:
		Niflect::TArrayNif<Niflect::CString> m_vecForRegularConversion;//header search paths for regular header file path conversion at writing code stage
		Niflect::TArrayNif<Niflect::CString> m_vecForBypassConversion;//header search paths for bypass header file path conversion at writing code stage
	};
}