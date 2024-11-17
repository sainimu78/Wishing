#pragma once
#include "Niflect/NiflectCommon.h"

namespace Niflect
{
	class CNiflectType;

	template <typename T>
	class TRegisteredType
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
	CNiflectType* TRegisteredType<T>::s_type = NULL;

	//现未确定是否有必要支持手工注册, 如确定有, 则保留默认实现, 否则仅保留声明并移除实现, 因为现已调整为TaggedType固定生成GeneratedBody中的StaticGetType特化, 因此不支持手工注册后不需要定义默认的实现
	template <typename T>
	CNiflectType* StaticGetType()
	{
		return TRegisteredType<T>::s_type;
	}
}