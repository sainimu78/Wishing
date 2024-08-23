#pragma once

//要求非模板的Accessor类型必须使用NIF_T标记
//2024.08.21, 现规划废弃此要求, 且 Accessor 可为一定规则的模板类
//#define TAGGED_REQUIREMENT_OF_NON_TEMPLATE_ACCESSOR_TYPE

//由用户提供 CCompoundField 类定义
//2024.08.23, 现 NiflectAccessor.h 中自带 CCompoundAccessor, 因为此类不需要自定义, 是复合结构(class, struct)的必要 Accessor 类型
//#define USER_PROVIDED_CCOMPONENTFIELD_CLASS_DEFINITION

//生成的SplittedModuleReg中调用TypeReg时需要专门namespace
//2024.08.23, 现为简化不需要namespace
//#define INVOKE_TYPEREG_WITH_NAMESPACE