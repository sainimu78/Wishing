#pragma once
#include "Niflect/NiflectBase.h"

namespace NiflectGen
{
	class CCommandLineArgs
	{
	public:
		static void CreateAccessor();

	public:
		Niflect::CString m_moduleName;
	};
}