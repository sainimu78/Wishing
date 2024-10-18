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

//现流程实现模板实例的Scope太繁琐, 如需要传入Detail的Cursor, 不确定BuildSubcursor能否正确处理namespace与类嵌套的Scope, 因此放弃
//#define TEMPLATE_INSTANCE_SCOPE

//类作为Scope
//#define CLASS_TYPE_SCOPE

//简化 TaggedType 的 IndexedRoot 初始化流程
//#define TODO_SIMPLIFY_TAGGED_TYPE_INDEXED_ROOT_INITIALIZATION

//实现枚举的代码生成流程, 如专门的 AccessorBinding, CodeWriter
//#define TODO_ENUM_CODE_GEN_PIPELINE

//BindingType 重复指定检查
//2024.10.18, 实验结论为, 未找到可行的通用办法实现重复指定 BindingType 检查. 对非模板别名具可行性, 但对于模板别名, 无法实现区分部分特化的情况
//	计划通过生成检查重复指定的代码实现正确性检查, 如生成基于 typeid(MyType).hash_code() 的检查代码
//#define BINDING_TYPE_DUPLICATION_VERIFICATION

//临时调试开关
//#define DEBUG_FOR_TYPE_REG