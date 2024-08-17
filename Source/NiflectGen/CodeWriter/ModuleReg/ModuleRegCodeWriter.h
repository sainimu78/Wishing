#pragma once
#include "NiflectGen/Resolver/Resolver.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCode.h"
#include "NiflectGen/CodeWriter/ModuleReg/SplittedModuleRegCode.h"
#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCode.h"

namespace NiflectGen
{
	struct SModuleRegIndicesAndIncludePath
	{
		Niflect::CString m_includePath_reserved;
		uint32 m_includePathPrivateHIndex;
	};

	class CTypeRegGenFileInfo
	{
	public:
		CTypeRegGenFileInfo(const Niflect::CString& prevateHIncludePath, const Niflect::CString& genHIncludePath)
			: m_prevateHIncludePath(prevateHIncludePath)
			, m_genHIncludePath(genHIncludePath)
		{

		}
		Niflect::CString m_prevateHIncludePath;
		Niflect::CString m_genHIncludePath;
		Niflect::TArrayNif<uint32> m_vecTypeRegDataIndex;
	};

	struct SModuleRegAndTypeRegMapping
	{
		Niflect::TMap<Niflect::CString, SModuleRegIndicesAndIncludePath> m_mapOriginalFilePathToModuleRegIndicesAndIncPath;
		Niflect::TArrayNif<uint32> m_vecTypeRegIndices;
		Niflect::TArrayNif<const Niflect::CString*> m_vecTypeRegIncludePathPrivateHRef;
	};

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
		void Write2(const CWritingContext& context, CCodeGenData& data);

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