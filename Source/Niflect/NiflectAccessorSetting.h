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

//可被绑定为此设置指定 Accessor 的类型有
//1. 带标记 NIF_T 的类型, 如 class, struct
//2. 结构模板(Structural Template), 如 std::pair
//此设置在模块范围内只可使用1次
//名称末尾的1表示 TSetting 模板需要指定的模板参数个数为1
#define NIF_AS_Compound_1() using NIFLECTGENINTERNAL_COMBINE(__NiflectGen_AccessorSetting_Compound,_,__LINE__) = 

//enum class 将绑定此设置指定的 Accessor
//此设置在模块范围内只可使用1次
//名称末尾的1表示 TSetting 模板需要指定的模板参数个数为1
#define NIF_AS_EnumClass_1() using NIFLECTGENINTERNAL_COMBINE(__NiflectGen_AccessorSetting_EnumClass,_,__LINE__) = 

//enum 将绑定此设置指定的 Accessor
//此设置在模块范围内只可使用1次
//名称末尾的1表示 TSetting 模板需要指定的模板参数个数为1
#define NIF_AS_EnumBitsMask_1() using NIFLECTGENINTERNAL_COMBINE(__NiflectGen_AccessorSetting_EnumBitsMask,_,__LINE__) = 

//可被绑定为此设置指定 Accessor 的类型有
//1. 容器模板(Container Template), 如 std::vector, std::map
//2. 所有能被 TCompount, TEnumClass, TEnumBitsMask 绑定的类型
//3. 特化模板, 如 std::vector<bool>
//此设置在模块范围内可多次使用, 以指定不同的类型的 Accessor 或覆盖其它设置指定的 Accessor
//名称末尾的2和3表示 TSetting 模板需要指定的模板参数个数为2或3
#define NIF_AS_Binding_2_3() using NIFLECTGENINTERNAL_COMBINE(__NiflectGen_AccessorSetting_Binding,_,__LINE__) = 

namespace NiflectAccessorSetting
{
	using TemplaateArgPlaceholder = void*;
	template <typename TAccessorType, typename TBindingType = TemplaateArgPlaceholder, typename TElementBindingType = TemplaateArgPlaceholder>
	class TSetting
	{
	};
}