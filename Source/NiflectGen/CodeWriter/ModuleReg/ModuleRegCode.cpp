#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCode.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Util/SystemUtil.h"

namespace NiflectGen
{
	void CModuleRegInfoValidated::Init(const CModuleRegInfo& info)
	{
		m_userProvided = info;
		m_moduleRegBasePath = NiflectUtil::ConcatPath(NiflectGenDefinition::DirName::ModuleReg, info.m_moduleName);
		m_typeRegBasePath = NiflectUtil::ConcatPath(NiflectGenDefinition::DirName::TypeReg, info.m_moduleName);
		m_outputRootPath = NiflectUtil::ConcatPath(m_userProvided.m_genBasePath, m_userProvided.m_genIncludeBasePath);

		NiflectUtil::DeleteDirectory(NiflectUtil::ConcatPath(m_outputRootPath, m_moduleRegBasePath));
		NiflectUtil::DeleteDirectory(NiflectUtil::ConcatPath(m_outputRootPath, m_typeRegBasePath));
	}
}