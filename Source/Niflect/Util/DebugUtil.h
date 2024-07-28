#pragma once
#include "Niflect/Base/NiflectBase.h"
#include "Niflect/Memory/Stats/NiflectMemoryStats.h"

namespace NiflectUtil
{
	static Niflect::CString DebugIndentToString(uint32 level, const Niflect::CString& singleIndentInString = "-")
	{
		auto curLevel = level;
		Niflect::CString strLevel;
		while (curLevel--)
			strLevel += singleIndentInString;
		return strLevel;
	}
}