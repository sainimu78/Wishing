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

		auto moduleGenDirPath = NiflectUtil::ConcatPath(info.m_outputRootPath_genIncludeSearchPath, info.m_moduleName);
		NiflectUtil::DeleteDirectory(moduleGenDirPath);

		m_moduleRegBasePath = NiflectGenDefinition::DirName::ModuleReg;
		m_typeRegBasePath = NiflectGenDefinition::DirName::TypeReg;
		m_genIncludeBasePath = NiflectGenDefinition::DirName::GenInclude;

		m_moduleRegisteredTypeHeaderFilePath = NiflectUtil::ConcatPath(m_typeRegBasePath, NiflectGenDefinition::NiflectFramework::FileName::ModuleRegisteredTypeHeader);
		m_moduleScopeSymbolPrefix = "_" + info.m_moduleName + "_";

		for (auto& it : m_userProvided.m_vecModuleHeaderSearchPath)
			m_writingHeaderSearchPaths.m_vecForRegularConversion.push_back(it);
		
		auto genTimeIncludeSearchDirPath = NiflectUtil::ConcatPath(moduleGenDirPath, NiflectGenDefinition::DirName::GenTime);
		genTimeIncludeSearchDirPath = CIncludesHelper::MakeIncludeSearchPath(genTimeIncludeSearchDirPath);
		GenerateBypassSTLHeaders(genTimeIncludeSearchDirPath);
		SGenTimeNiflectMacroHeaderWritingContext ctx{ m_userProvided.m_vecModuleHeaderSearchPath, genTimeIncludeSearchDirPath };
		WriteGenTimeNiflectMacroHeader(ctx);

		m_writingHeaderSearchPaths.m_vecForGenTimeConversion.push_back(genTimeIncludeSearchDirPath);

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
}