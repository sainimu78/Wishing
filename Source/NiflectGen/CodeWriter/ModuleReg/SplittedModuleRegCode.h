#pragma once
#include "NiflectGen/CodeWriter/CodeWriter.h"

namespace NiflectGen
{
	struct SSplittedModuleRefInfo
	{
		const CTypeRegWritingData* m_typeRegData;
		const Niflect::CString* m_includePathPrivateH;
	};

	class SSplittedModuleRegWritingContext
	{
	public:
		const Niflect::CString& m_moduleName;
		const Niflect::CString& m_moduleRegBasePath;
		const Niflect::TArrayNif<SSplittedModuleRefInfo>& m_vecTypeRegRefInfo;
	};

	class CSplittedModuleRegGenData
	{
	public:
		CCodeLines m_h;
		CCodeLines m_cpp;
		Niflect::CString m_includePath;
	};

	class CSplittedModuleRegInvokationData
	{
	public:
		CCodeLines m_codeInitTables;
		CCodeLines m_invokationRegisterTypes;
		CCodeLines m_invokationInitTypes;
	};
}