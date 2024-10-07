#pragma once
#include "NiflectGen/Resolver/Resolver.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCode.h"
#include "NiflectGen/CodeWriter/ModuleReg/SplittedModuleRegCode.h"
#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCode.h"

namespace NiflectGen
{
	class CModuleRegGenData
	{
	public:
		CCodeLines m_privateH;
		Niflect::CString m_privateHIncludePath;
	};

	class CTypeRegGenData
	{
	public:
		CCodeLines m_genH;
		Niflect::CString m_genHIncludePath;
		CCodeLines m_privateH;
		Niflect::CString m_privateHIncludePath;
	};

	class CCodeGenData
	{
	public:
		CModuleRegGenData m_moduleRegGenData;
		Niflect::TArrayNif<CSplittedModuleRegGenData> m_vecSplittedModuleRegGenData;
		Niflect::TArrayNif<CTypeRegGenData> m_vecTypeRegGenData;
	};

	class CTemplateBasedCppWriter
	{
	public:
		CTemplateBasedCppWriter(const CResolvedData& resolvedData, const CModuleRegInfoValidated& moduleRegInfo);

	public:
		//void Write();
		void Deprecated_Write2(const CWritingContext& context, CCodeGenData& data);
		void Write3(const CWritingContext& context, CCodeGenData& data);

	private:
		void WriteTypeRegs(const CWritingContext& context, Niflect::TArrayNif<CTypeRegWritingData>& vecTypeRegData);
		//void WriteModuleRegs(const CWritingContext& context, const Niflect::TArrayNif<CTypeRegWritingData>& vecTypeRegData, Niflect::TArrayNif<CModuleRegWritingData>& vecModuleRegData);
		void CreateWriters(const CWritingContext& context, Niflect::TArrayNif<CTypeRegGenFileInfo>& vecTypeRegGenFileInfo);

	private:
		const CResolvedData& m_resolvedData;
		const CModuleRegInfoValidated& m_moduleRegInfo;
		Niflect::TArrayNif<Niflect::TSharedPtr<CTypeRegCodeWriter> > m_vecWriter;
		SModuleRegAndTypeRegMapping m_mapping;
	};
}