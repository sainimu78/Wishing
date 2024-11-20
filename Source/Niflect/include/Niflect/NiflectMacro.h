#pragma once
#include "Niflect/Util/ConcatSymbols.h"

#ifdef NIFLECTGEN
${GenTimeReplacement}
#else
// Include a redundant semicolon at the end of the generated code block, so that intellisense parsers can start parsing
// a new declaration if the line number/generated code is out of date.
#define GENERATED_BODY(...) CONCAT_SYMBOLS_4(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY);

#define NIFLECTGENTAG_TYPE 
#define NIFLECTGENTAG_FIELD 
#define NIFLECTGENTAG_METHOD 
#define NIFLECTGENTAG_ENUMCONST
#endif

#define NIF_T(...) NIFLECTGENTAG_TYPE

#define NIF_F(...) NIFLECTGENTAG_FIELD

#define NIF_M(...) NIFLECTGENTAG_METHOD

#define NIF_C(...) NIFLECTGENTAG_ENUMCONST