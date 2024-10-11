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
		//Niflect::TArrayNif<CSplittedGenData> m_vecSplittedTypeRegGenData;
		Niflect::TArrayNif<CTypeRegGenData> m_vecTypeRegGenData;
	};

	class CSplittedModuleReg2
	{
	public:
		Niflect::TArrayNif<const CTypeRegWritingData2*> m_vecTypeRegDataRef;
	};

	class CSplittedModuleRegWritingContext
	{
	public:
		CSplittedModuleRegWritingContext(CGenLog* log);

	public:
		//void Write(const SSplittedModuleRegWritingContext2& context, CSplittedModuleRegWritingData2& data) const;

	public:
		Niflect::TArrayNif<CSplittedModuleReg2> m_vecItem;
		CGenLog* m_log;
	};

	struct SSplittedTypeRegWritingData
	{
		Niflect::TArrayNif<CTypeRegGenData>& m_vecTypeRegGenData;
	};
	struct SSplittedModuleRegWritingData2
	{
		Niflect::TArrayNif<CSplittedModuleRegGenData>& m_vecSplittedModuleRegGenData;
		Niflect::TArrayNif<Niflect::CString>& m_vecSplittedModuleRegFuncName;
	};

	struct SModuleRegWritingContext2
	{
		const Niflect::TArrayNif<CSplittedModuleReg2>& m_vecItem;
		const Niflect::TArrayNif<Niflect::CString>& m_vecSplittedModuleRegFuncName;
		const Niflect::TArrayNif<CSplittedModuleRegGenData>& m_vecSplittedModuleRegGenData;
		CGenLog* m_log;
	};
	struct SModuleRegWritingData2
	{
		CModuleRegGenData& m_moduleRegGenData;
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
		void CreateWriters3(const CWritingContext& context, Niflect::TArrayNif<CTypeRegGenFileInfo>& vecTypeRegGenFileInfo);
		void WriteTypeRegs3(const CWritingContext& context, Niflect::TArrayNif<CTypeRegWritingData2>& vecTypeRegData);
		void WriteSplittedTypeRegs(const CSplittedModuleRegWritingContext& context, SSplittedTypeRegWritingData& data) const;
		void WriteSplittedModuleRegs2(const CSplittedModuleRegWritingContext& context, SSplittedModuleRegWritingData2& data) const;
		void WriteModuleReg(const SModuleRegWritingContext2& context, SModuleRegWritingData2& data) const;

	private:
		const CResolvedData& m_resolvedData;
		const CModuleRegInfoValidated& m_moduleRegInfo;
		Niflect::TArrayNif<Niflect::TSharedPtr<CTypeRegCodeWriter> > m_vecWriter;
		SModuleRegAndTypeRegMapping m_mapping;
		Niflect::TArrayNif<CSharedTypeRegCodeWriter2> m_vecWriter2;
	};
}