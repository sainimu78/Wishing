#pragma once
#include "NiflectGen/CodeWriter/CodeWriter.h"

namespace NiflectGen
{
	class CModuleRegInfo
	{
	public:
		Niflect::CString m_moduleName;
		Niflect::CString m_genIncludeBasePath;
		Niflect::CString m_genBasePath;
		Niflect::TArrayNif<Niflect::CString> m_vecOriginalHeader;
		Niflect::TArrayNif<Niflect::CString> m_vecBindingSettingHeader;
		//Niflect::TArrayNif<Niflect::CString> m_vecDependencyHeader;
		Niflect::TArrayNif<Niflect::CString> m_vecParsingHeaderSearchPath;//header search paths for libclang parsing
		CWritingHeaderSearchPaths m_writingHeaderSearchPaths;
	};

	namespace Test
	{
		static void AddHeaderSearchPaths(Niflect::TArrayNif<Niflect::CString>& vecParsingHeaderSearchPath, CWritingHeaderSearchPaths& writingHeadaerSearchPaths)
		{
			writingHeadaerSearchPaths.m_vecForRegularConversion.push_back("F:/Fts/Proj/Test/Interedit/Source");
			//todo: 旁路代码极简单, 可考虑只在内存中生成
			writingHeadaerSearchPaths.m_vecForBypassConversion.push_back("F:/Fts/Proj/Test/Interedit/Source/BypassCode/NiflectSTL");

			for (auto& it : writingHeadaerSearchPaths.m_vecForRegularConversion)
				vecParsingHeaderSearchPath.push_back(it);
			for (auto& it : writingHeadaerSearchPaths.m_vecForBypassConversion)
				vecParsingHeaderSearchPath.push_back(it);
		}
	}

	class CModuleRegInfoValidated
	{
	public:
		CModuleRegInfoValidated(const CModuleRegInfo& info);
		//void Validate();
		//void Init(const CModuleInfo& info);

		Niflect::CString m_typeRegBasePath;
		Niflect::CString m_moduleRegBasePath;
		CModuleRegInfo m_userProvided;
	};
}