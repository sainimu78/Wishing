#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCode.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"

namespace NiflectGen
{
	CModuleRegInfoValidated::CModuleRegInfoValidated(const CModuleRegInfo& info)
		: m_userProvided(info)
		, m_moduleRegBasePath(NiflectUtil::ConcatPath(NiflectGenDefinition::RelativeDirPath::ModuleReg, info.m_moduleName))
		, m_typeRegBasePath(NiflectUtil::ConcatPath(NiflectGenDefinition::RelativeDirPath::TypeReg, info.m_moduleName))
	{
		//todo: 路径有效性检查, 重复路径剔除等
	}
}