#pragma once

//todo: 支持类型反射的选项, 如默认反射所有成员变量以方便使用

#ifdef NIFLECTGEN
#define GENERATED_BODY(...) typedef void* __NiflectGen_GeneratedBody;

#define NIFLECTGENTAG_TYPE typedef void* __NiflectGen_Type;
#define NIFLECTGENTAG_FIELD typedef void* __NiflectGen_Field;
#define NIFLECTGENTAG_METHOD typedef void* __NiflectGen_Method;
#define NIFLECTGENTAG_CONSTANT __attribute__((annotate("__NiflectGen_EnumConstant")))
#else
#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)

// Include a redundant semicolon at the end of the generated code block, so that intellisense parsers can start parsing
// a new declaration if the line number/generated code is out of date.
#define GENERATED_BODY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY)

#define NIFLECTGENTAG_TYPE 
#define NIFLECTGENTAG_FIELD 
#define NIFLECTGENTAG_METHOD 
#define NIFLECTGENTAG_CONSTANT
#endif

#define NIF_T(...) NIFLECTGENTAG_TYPE

#define NIF_F(...) NIFLECTGENTAG_FIELD

#define NIF_M(...) NIFLECTGENTAG_METHOD

#define NIF_C(...) NIFLECTGENTAG_CONSTANT