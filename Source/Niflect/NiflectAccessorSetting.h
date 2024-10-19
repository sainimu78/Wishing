#pragma once

//#define NIFLECTGENINTERNAL_COMBINE_INNER(A,B,C) A##B##C
//#define NIFLECTGENINTERNAL_COMBINE(A,B,C) NIFLECTGENINTERNAL_COMBINE_INNER(A,B,C)
//
//#define NIF_AS() using NIFLECTGENINTERNAL_COMBINE(__NiflectGen_AccessorSetting,_,__LINE__) = 
//
//namespace NiflectAccessorSetting
//{
//	//可被绑定为此设置指定 Accessor 的类型有
//	//1. 带标记 NIF_T 的类型, 如 class, struct
//	//2. 结构模板(Structural Template), 如 std::pair
//	//此设置在模块范围内只使用1次
//	template <typename TAccessorType>
//	class TCompound
//	{
//	};
//
//	//enum class 将绑定此设置指定的 Accessor
//	//此设置在模块范围内只使用1次
//	template <typename TAccessorType>
//	class TEnumClass
//	{
//	};
//
//	//enum 将绑定此设置指定的 Accessor
//	//此设置在模块范围内只使用1次
//	template <typename TAccessorType>
//	class TEnumBitsMask
//	{
//	};
//
//	using BindingTypePlaceholder = void*;
//
//	//可被绑定为此设置指定 Accessor 的类型有
//	//1. 容器模板(Container Template), 如 std::vector, std::map
//	//2. 所有能被 TCompount, TEnumClass, TEnumBitsMask 绑定的类型
//	//3. 特化模板, 如 std::vector<bool>
//	//此设置在模块范围内可多次使用, 以指定不同的类型的 Accessor 或覆盖其它设置指定的 Accessor
//	template <typename TAccessorType, typename TBindingType, typename TElementBindingType = BindingTypePlaceholder>
//	class TBinding
//	{
//	};
//}















#define NIFLECTGENINTERNAL_COMBINE_INNER(A,B,C) A##B##C
#define NIFLECTGENINTERNAL_COMBINE(A,B,C) NIFLECTGENINTERNAL_COMBINE_INNER(A,B,C)

//General Accessor 设置, 简称 A 型设置
//可被绑定为此设置指定 Accessor 的类型有
//1. 容器模板(Container Template 1D), 如 std::vector, std::map
//2. 结构模板(Structural Template nD, n>=2), 如 std::pair
//3. 特化模板, 如 std::vector<bool>
//4. 所有能被其它类型设置所绑定的类型, 因此, A 型设置也可理解为一种覆盖设置
//此设置在模块范围内可多次使用, 以指定不同的类型的 Accessor 或覆盖其它设置指定的 Accessor
//TSetting 模板需要指定的模板参数个数为2或3
#define NIF_AS_A() using NIFLECTGENINTERNAL_COMBINE(__NiflectGen_AccessorSetting_A,_,__LINE__) = 

//Compound Accessor 设置, 简称 B 型设置
//带标记 NIF_T 的类型, 如 class, struct
//当未指定类型的 A 型设置时, 则类型绑定此设置指定的 Accessor
//此设置在模块范围内只可使用1次
//TSetting 模板需要指定的模板参数个数为1
#define NIF_AS_B() using NIFLECTGENINTERNAL_COMBINE(__NiflectGen_AccessorSetting_B,_,__LINE__) = 

//Enum Class Accessor 设置, 简称 C 型设置
//enum class 将绑定此设置指定的 Accessor
//当未指定类型的 A 型设置时, 则类型绑定此设置指定的 Accessor
//此设置在模块范围内只可使用1次
//TSetting 模板需要指定的模板参数个数为1
#define NIF_AS_C() using NIFLECTGENINTERNAL_COMBINE(__NiflectGen_AccessorSetting_C,_,__LINE__) = 

//Enum Bits Mask Accessor 设置, 简称 D 型设置
//enum 将绑定此设置指定的 Accessor
//当未指定类型的 A 型设置时, 则类型绑定此设置指定的 Accessor
//此设置在模块范围内只可使用1次
//TSetting 模板需要指定的模板参数个数为1
#define NIF_AS_D() using NIFLECTGENINTERNAL_COMBINE(__NiflectGen_AccessorSetting_D,_,__LINE__) = 

namespace NiflectAccessorSetting
{
	using TemplaateArgPlaceholder = void*;
	template <typename TAccessorType, typename TBindingType = TemplaateArgPlaceholder, typename TElementBindingType = TemplaateArgPlaceholder>
	class TSetting
	{
	};
}