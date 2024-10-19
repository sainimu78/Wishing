#include "EngineCommon.h"

ENGINE_API void TestAPI_Cpp();
ENGINE_C_API void TestAPI_C();

//Niflect::CNiflectRegistration* TestCreateModuleReg0();
//void TestDestroyModuleReg0();

#ifdef ENABLED_TEST_MODULEREG_GEN_BY_NGT
ENGINE_API void TestEngineCreate();
ENGINE_API void TestEngineRun();
ENGINE_API void TestEngineDestroy();
#endif