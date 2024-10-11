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

		////begin, 已验证无法通过特化区分原始类型与别名(using和typedef定义的别名)
		//template <typename T2>
		//friend void __InternalStaticSetType(CNiflectType* type);
		//template <typename T2>
		//friend bool __InternalStaticIsValid();
		////end

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

	template <typename T>
	CNiflectType* StaticGetType()
	{
		return TRegisteredType<T>::s_type;
	}

	template <typename T>
	using TInternalRegisteredType = TRegisteredType<T>;//旧代码兼容, 一定阶段后移除
	

	////begin, 已验证无法通过特化区分原始类型与别名(using和typedef定义的别名)
	//template <typename T>
	//void __InternalStaticSetType(CNiflectType* type)
	//{
	//	TRegisteredType<T>::s_type = type;
	//}
	//template <typename T>
	//bool __InternalStaticIsValid()
	//{
	//	return TRegisteredType<T>::s_type != NULL;
	//}
	////end
}