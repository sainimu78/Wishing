#pragma once
#include "NiflectGen/CodeWriter/ModuleReg/SplittedModuleRegCode.h"

namespace NiflectGen
{
    void WriteSplittedCreateTypeAccessorSpec(const SSplittedCreateTypeAccessorSpecWritingContext& context, SSplittedCreateTypeAccessorSpecWritingData& data);
    void WriteSplittedModuleRegs3(const SSplittedModuleRegWritingContext2& context, SSplittedModuleRegWritingData2& data);
}