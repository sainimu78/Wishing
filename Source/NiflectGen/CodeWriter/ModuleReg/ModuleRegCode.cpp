#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCode.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Util/SystemUtil.h"
#include "NiflectGen/Generator/BypassSTLHeaders.h"

namespace NiflectGen
{
	bool CModuleRegInfoValidated::Init(const CModuleRegInfo& info)
	{
		if (info.m_moduleName.empty())
			return false;

		m_userProvided = info;

		auto moduleGenDirPath = NiflectUtil::ConcatPath(info.m_outputRootPath_genIncludeSearchPath, info.m_moduleName);
		NiflectUtil::DeleteDirectory(moduleGenDirPath);

		m_moduleRegBasePath = NiflectUtil::ConcatPath(info.m_moduleName, NiflectGenDefinition::DirName::ModuleReg);
		m_typeRegBasePath = NiflectUtil::ConcatPath(info.m_moduleName, NiflectGenDefinition::DirName::TypeReg);
		m_genHBasePath = NiflectUtil::ConcatPath(info.m_moduleName, NiflectGenDefinition::DirName::GenH);

		m_moduleRegisteredTypeHeaderFilePath = NiflectUtil::ConcatPath(m_typeRegBasePath, NiflectGenDefinition::NiflectFramework::FileName::ModuleRegisteredTypeHeader);
		m_moduleScopeSymbolPrefix = "_" + info.m_moduleName + "_";

		for (auto& it : m_userProvided.m_vecModuleHeaderSearchPath)
			m_writingHeaderSearchPaths.m_vecForRegularConversion.push_back(it);
		
		auto bypassSTL = NiflectUtil::ConcatPath(moduleGenDirPath, NiflectGenDefinition::NiflectFramework::BypassSTL::HeadersDirName);
		GenerateBypassSTLHeaders(bypassSTL);

		m_writingHeaderSearchPaths.m_vecForBypassConversion.push_back(bypassSTL);

		for (auto& it : m_writingHeaderSearchPaths.m_vecForRegularConversion)
			m_vecParsingHeaderSearchPath.push_back(it);
		for (auto& it : m_writingHeaderSearchPaths.m_vecForBypassConversion)
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