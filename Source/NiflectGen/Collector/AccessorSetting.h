#pragma once
#include "Niflect/NiflectCommon.h"
#include "Niflect/Util/ConstCharConcat.h"

#define CODETAG_PREFIX_ACCESSOR_SETTING "__NiflectGen_AccessorSetting"

namespace NiflectGen
{
	enum class EAccessorSettingTagType
	{
		A,
		B,
		C,
		D,
		Count,
	};
	//constexpr const char* AccessorSetting = CODETAG_PREFIX_ACCESSOR_SETTING;
	constexpr const char* AccessorSetingTagNames[] = {
		CONCAT_CONST_CHAR_2(CODETAG_PREFIX_ACCESSOR_SETTING, "_A"),
		CONCAT_CONST_CHAR_2(CODETAG_PREFIX_ACCESSOR_SETTING, "_B"),
		CONCAT_CONST_CHAR_2(CODETAG_PREFIX_ACCESSOR_SETTING, "_C"),
		CONCAT_CONST_CHAR_2(CODETAG_PREFIX_ACCESSOR_SETTING, "_D")
	};
	static uint32 GetAccessorSettingTypesCount()
	{
		return static_cast<uint32>(EAccessorSettingTagType::Count);
	}
}