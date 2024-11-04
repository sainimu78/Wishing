#pragma once
#include "NiflectGen/CodeWriter/CodeWriter.h"

namespace NiflectGen
{
	enum class EGeneratingHeaderAndSourceFileMode
	{
		EHeaderOnly,

		//使用此模式须将生成的文件接入 Build 系统, 以支持在生成后无须执行 Module 的 cmake
		//如未接入 Build 系统, 仅须执行 Module 的 cmake, 将生成的文件加入 Module 即可
		//此模式通常用于方便调试生成的代码, 或利用多处理器编译, 一般情况不使用
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