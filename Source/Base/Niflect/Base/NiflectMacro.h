#pragma once

//todo: 支持类型反射的选项, 如默认反射所有成员变量以方便使用(考虑UE为何不支持这种用法)

#ifdef NIFLECTGEN
#define NIFLECTGENTAG_TYPE typedef void* __NiflectGen_Type;
#define NIFLECTGENTAG_FIELD typedef void* __NiflectGen_Field;
#define NIFLECTGENTAG_METHOD typedef void* __NiflectGen_Method;
#define NIFLECTGENTAG_CONSTANT __attribute__((annotate("__NiflectGen_EnumConstant")))
#else
#define NIFLECTGENTAG_TYPE 
#define NIFLECTGENTAG_FIELD 
#define NIFLECTGENTAG_METHOD 
#define NIFLECTGENTAG_CONSTANT
#endif

//todo: 应指定Gen解析专用宏, 避免冗余定义
#define NIF_T(...) NIFLECTGENTAG_TYPE

#define NIF_F(...) NIFLECTGENTAG_FIELD

#define NIF_M(...) NIFLECTGENTAG_METHOD

#define NIF_C(...) NIFLECTGENTAG_CONSTANT

#define NIF_FRIEND(className)\
	friend class CInheritableTypeReg_##className;

class CTestClassInNiflectMacroHeader
{
};