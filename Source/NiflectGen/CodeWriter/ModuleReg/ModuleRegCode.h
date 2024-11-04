#pragma once
#include "NiflectGen/CodeWriter/CodeWriter.h"

namespace NiflectGen
{
	enum class EGeneratingHeaderAndSourceFileMode
	{
		EHeaderOnly,
		ESourceAndHeader,
	};

	class CModuleRegInfo
	{
	public:
		CModuleRegInfo()
			: m_genFileMode(EGeneratingHeaderAndSourceFileMode::EHeaderOnly)
		{
		}
		Niflect::CString m_moduleName;
		Niflect::CString m_genIncludeBasePath;
		Niflect::CString m_genBasePath;
		Niflect::TArrayNif<Niflect::CString> m_vecModuleHeader;
		Niflect::TArrayNif<Niflect::CString> m_vecAccessorSettingHeader;
		Niflect::TArrayNif<Niflect::CString> m_vecParsingHeaderSearchPath;//header search paths for libclang parsing
		CWritingHeaderSearchPaths m_writingHeaderSearchPaths;
		Niflect::CString m_moduleApiMacro;
		Niflect::CString m_moduleApiMacroHeader;
		EGeneratingHeaderAndSourceFileMode m_genFileMode;
	};

	class CModuleRegInfoValidated
	{
	public:
		void Init(const CModuleRegInfo& info);

		Niflect::CString m_typeRegBasePath;
		Niflect::CString m_genHBasePath;
		Niflect::CString m_moduleRegBasePath;
		CModuleRegInfo m_userProvided;
		Niflect::CString m_outputRootPath;
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

}