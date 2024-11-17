#pragma once
#include "NiflectGen/Generator/SourceInMemory.h"
#include "NiflectGen/Log/Log.h"

namespace NiflectGen
{
	struct SGenTimeNiflectMacroHeaderWritingContext
	{
		const Niflect::TArrayNif<Niflect::CString>& m_vecModuleHeaderSearchPath;
		const Niflect::CString& m_moduleGenIncludeSearchDirPath;
	};
	void WriteGenTimeNiflectMacroHeader(const SGenTimeNiflectMacroHeaderWritingContext& context);
}