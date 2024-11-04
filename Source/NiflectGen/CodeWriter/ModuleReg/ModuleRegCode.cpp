#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCode.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Util/SystemUtil.h"
//#include "Niflect/Util/StringUtil.h"

namespace NiflectGen
{
	void CModuleRegInfoValidated::Init(const CModuleRegInfo& info)
	{
		m_userProvided = info;
		m_moduleRegBasePath = NiflectUtil::ConcatPath(info.m_moduleName, NiflectGenDefinition::DirName::ModuleReg);
		m_typeRegBasePath = NiflectUtil::ConcatPath(info.m_moduleName, NiflectGenDefinition::DirName::TypeReg);
		m_genHBasePath = NiflectUtil::ConcatPath(info.m_moduleName, NiflectGenDefinition::DirName::GenH);

		//if (m_userProvided.m_specifiedModuleApiMacro.empty())
		//	m_moduleApiMacro = NiflectUtil::FormatString("%s_API", NiflectUtil::ConvertToUpperCase(info.m_moduleName).c_str());

		NiflectUtil::DeleteDirectory(NiflectUtil::ConcatPath(info.m_outputRootPath_genIncludeSearchPath, info.m_moduleName));
	}
	Niflect::CString CModuleRegInfoValidated::GetSourceFileExtForGenFileMode() const
	{
		if (m_userProvided.m_genFileMode == EGeneratingHeaderAndSourceFileMode::EHeaderOnly)
			return NiflectGenDefinition::FileExt::PrivateH;
		return NiflectGenDefinition::FileExt::Cpp;
	}
}