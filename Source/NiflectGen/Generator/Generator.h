#pragma once
#include "NiflectGen/NiflectGenCommon.h"
#include "NiflectGen/Generator/SourceInMemory.h"
#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCode.h"

namespace NiflectGen
{
	class CDataCollector;
	class CCodeGenData;

	class CGenerator
	{
	public:
		CGenerator();

	public:
		NIFLECTGEN_API void AddTypeBindingSettingHeader(const Niflect::CString& filePath);
		NIFLECTGEN_API void AddFileForSearching(const Niflect::CString& filePath);
		NIFLECTGEN_API void AddIncludePath(const Niflect::CString& dirPath);
		NIFLECTGEN_API void ParseSourceFiles();
		NIFLECTGEN_API void SetModuleRegInfo(const CModuleRegInfo& moduleRegInfo);
		NIFLECTGEN_API void Generate();
		NIFLECTGEN_API void Save() const;

	private:
		void PrepareSourceFiles();
		void GetUnsavedSourceFiles(Niflect::TArrayNif<CXUnsavedFile>& vecUnsavedFileHandle);

	private:
		Niflect::TArrayNif<Niflect::CString> m_vecTypeBindingSettingFilePath;
		CSourceInMemory m_tempSource;
		Niflect::TArrayNif<Niflect::CString> m_vecFileForSearchingCpp;
		Niflect::TArrayNif<Niflect::CString> m_vecFileForSearchingH;
		Niflect::TArrayNif<Niflect::CString> m_vecHeaderSearchPath;
		Niflect::TSharedPtr<CDataCollector> m_collectorHolder;//仅为不包含头文件, 避免使用该类的工程需要添加clang头文件路径
		CDataCollector& m_collector;
		CModuleRegInfo m_moduleRegInfo;
		Niflect::TSharedPtr<CCodeGenData> m_genDataHolder;
		CCodeGenData& m_genData;
	};

	NIFLECTGEN_API Niflect::TSharedPtr<CGenerator> CreateGenerator();

	//S3ENGINE_API2 Niflect::TSharedPtr<CTypeBindingTable> CreateTypeBindingTable();
	NIFLECTGEN_API void InitTypeBindingTable();
	NIFLECTGEN_API void TestMustache();
}