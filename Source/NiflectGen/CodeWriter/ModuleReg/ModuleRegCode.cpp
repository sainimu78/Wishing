#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCode.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Util/SystemUtil.h"
#include "NiflectGen/Generator/BypassSTLHeaders.h"
#include "NiflectGen/CodeWriter/GenTimeNiflectMacro.h"
#include "NiflectGen/CodeWriter/CppWriter.h"

namespace NiflectGen
{
	bool CModuleRegInfoValidated::Init(const CModuleRegInfo& info)
	{
		if (info.m_moduleName.empty())
			return false;

		m_userProvided = info;

		auto moduleGenDirPath = NiflectUtil::ConcatPath(info.m_genOutputDirPath, info.m_moduleName);
		NiflectUtil::DeleteDirectory(moduleGenDirPath);
		if (!info.m_genSourceOutputDirPath.empty())
		{
			auto genSourceOutputDirPath = NiflectUtil::ConcatPath(info.m_genSourceOutputDirPath, info.m_moduleName);
			NiflectUtil::DeleteDirectory(genSourceOutputDirPath);
		}

		m_moduleGenSource = NiflectGenDefinition::DirName::GenSource;
		m_moduleRegBasePath = NiflectGenDefinition::DirName::ModuleReg;
		m_typeRegBasePath = NiflectGenDefinition::DirName::TypeReg;
		m_genIncludeBasePath = NiflectGenDefinition::DirName::GenInclude;

		m_moduleRegisteredTypeHeaderFilePath = NiflectUtil::ConcatPath(m_typeRegBasePath, NiflectGenDefinition::NiflectFramework::FileName::ModuleRegisteredTypeHeader);
		m_moduleScopeSymbolPrefix = "_" + info.m_moduleName + "_";

		for (auto& it : m_userProvided.m_vecModuleHeaderSearchPath2)
			m_writingHeaderSearchPaths.m_vecForRegularConversion.push_back(it);
		//须添加在最后, NiflectMacro.h 应使用 _GenTime 中生成的, 而 NiflectMacro.h 仍须使用 m_toolHeaderSearchPath 中的其它头文件, 如 ConcatSymbols.h
		m_writingHeaderSearchPaths.m_vecForRegularConversion.push_back(m_userProvided.m_toolHeaderSearchPath);
		
		auto genTimeBasePath = NiflectUtil::ConcatPath(moduleGenDirPath, NiflectGenDefinition::DirName::GenTime);
		GenerateBypassSTLHeaders(genTimeBasePath);
		{
			CGenLog log;
			Niflect::TArrayNif<Niflect::CString> vecToolHeaderSearchPath;
			vecToolHeaderSearchPath.push_back(m_userProvided.m_toolHeaderSearchPath);
			SGenTimeNiflectMacroHeaderWritingContext ctx{ vecToolHeaderSearchPath, genTimeBasePath, &log };
			WriteGenTimeNiflectMacroHeader(ctx);
		}

		m_writingHeaderSearchPaths.m_vecForGenTimeConversion.push_back(NiflectUtil::ConvertToSearchPath(genTimeBasePath));

		for (auto& it : m_writingHeaderSearchPaths.m_vecForGenTimeConversion)
			m_vecParsingHeaderSearchPath.push_back(it);
		for (auto& it : m_writingHeaderSearchPaths.m_vecForRegularConversion)
			m_vecParsingHeaderSearchPath.push_back(it);

		//if (m_userProvided.m_specifiedModuleApiMacro.empty())
		//	m_moduleApiMacro = NiflectUtil::FormatString("%s_API", NiflectUtil::ConvertToUpperCase(info.m_moduleName).c_str());

		return true;
	}
	Niflect::CString CModuleRegInfoValidated::GetSourceFileExtForGenFileMode() const
	{
		if (m_userProvided.m_genFileMode == EGeneratingHeaderAndSourceFileMode::EHeaderOnly)
			return NiflectGenDefinition::FileExt::PrivateH;
		return NiflectGenDefinition::FileExt::Cpp;
	}
	namespace Test
	{
		void InitArgs(CModuleRegInfo& info)
		{
			info.m_moduleName = "Engine";
			info.m_genOutputDirPath = CONCAT_HARDCODED_STRINGS_2(ROOT_TEST_PROJECT_PATH, "/Generated/NiflectGenerated");
			info.m_vecModuleHeaderSearchPath2.push_back(CONCAT_HARDCODED_STRINGS_2(ROOT_TEST_INCLUDE_PATH, "/Engine/include"));
			info.m_toolHeaderSearchPath = CONCAT_HARDCODED_STRINGS_2(ROOT_TEST_INCLUDE_PATH, "/Niflect/include");
			info.m_vecModuleHeaderSearchPath2.push_back(ROOT_TEST_INCLUDE_PATH);
		}
	}
}