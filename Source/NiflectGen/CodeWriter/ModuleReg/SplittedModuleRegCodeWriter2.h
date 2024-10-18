#pragma once
#include "NiflectGen/CodeWriter/ModuleReg/SplittedModuleRegCode.h"

namespace NiflectGen
{
    void WriteSplittedFieldLayoutSpec(const SSplittedFieldLayoutSpecWritingContext& context, SSplittedFieldLayoutSpecWritingData& data);
    void WriteSplittedModuleRegs3(const SSplittedModuleRegWritingContext2& context, SSplittedModuleRegWritingData2& data);
}