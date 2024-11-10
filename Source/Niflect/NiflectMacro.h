#pragma once
#include "Niflect/Util/ConcatSymbols.h"

#ifdef NIFLECTGEN
	#define GENERATED_BODY(...) typedef void* CONCAT_SYMBOLS_2(__NiflectGen_GeneratedBody,__LINE__);

	#define NIFLECTGENTAG_TYPE typedef void* __NiflectGen_Type;

	#ifdef WIN32
	#define NIFLECTGENTAG_FIELD typedef void* __NiflectGen_Field;
	#else
	#define NIFLECTGENTAG_FIELD typedef void* CONCAT_SYMBOLS_2(__NiflectGen_Field,__LINE__);
	#endif

	#define NIFLECTGENTAG_METHOD typedef void* __NiflectGen_Method;

	#define NIFLECTGENTAG_CONSTANT __attribute__((annotate("__NiflectGen_EnumConstant")))
#else

// Include a redundant semicolon at the end of the generated code block, so that intellisense parsers can start parsing
// a new declaration if the line number/generated code is out of date.
#define GENERATED_BODY(...) CONCAT_SYMBOLS_4(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY);

#define NIFLECTGENTAG_TYPE 
#define NIFLECTGENTAG_FIELD 
#define NIFLECTGENTAG_METHOD 
#define NIFLECTGENTAG_CONSTANT
#endif

#define NIF_T(...) NIFLECTGENTAG_TYPE

#define NIF_F(...) NIFLECTGENTAG_FIELD

#define NIF_M(...) NIFLECTGENTAG_METHOD

#define NIF_C(...) NIFLECTGENTAG_CONSTANT