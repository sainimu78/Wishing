#pragma once
#include "Niflect/NiflectBase.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCode.h"
#include "NiflectGen/CodeWriter/ModuleReg/SplittedModuleRegCode.h"

namespace NiflectGen
{
	void WriteSplittedModuleRegs(const CWritingContext& context, const SSplittedModuleRegWritingContext& writingCtx, Niflect::TArrayNif<CSplittedModuleRegInvokationData>& vecSplittedModuleRegInvokationData, Niflect::TArrayNif<CSplittedModuleRegGenData>& vecSplittedModuleRegData);
}