#pragma once

namespace NiflectGen
{
	class CSplittedModuleRegGenData
	{
	public:
		CCodeLines m_h;
		CCodeLines m_cpp;
		Niflect::CString m_headerFilePath;
	};

	class CTypeRegGenData
	{
	public:
		CCodeLines m_genH;
		Niflect::CString m_genHIncludePath;
		CCodeLines m_privateH;
		Niflect::CString m_privateHIncludePath;
	};

	class CCreateTypeAccessorSpecData
	{
	public:
		CCodeLines m_decl;
		Niflect::CString m_declHeaderFilePath;
		CCodeLines m_impl;
		Niflect::CString m_implHeaderFilePath;
	};

	class CModuleRegGenData
	{
	public:
		CCodeLines m_privateH;
		Niflect::CString m_privateHIncludePath;
	};

	class CCodeGenData
	{
	public:
		CModuleRegGenData m_moduleRegGenData;
		Niflect::TArrayNif<CSplittedModuleRegGenData> m_vecSplittedModuleRegGenData;
		//Niflect::TArrayNif<CSplittedGenData> m_vecSplittedTypeRegGenData;
		Niflect::TArrayNif<CTypeRegGenData> m_vecTypeRegGenData;
		Niflect::TArrayNif<CCreateTypeAccessorSpecData> m_vecCreateTypeAccessorSpecGenData;
	};
}