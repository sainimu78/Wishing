#pragma once
#include "Niflect/NiflectBase.h"

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
		Niflect::TArrayNif<Niflect::CString> m_vecHeaderSearchPath;
	};

	class CModuleRegInfoValidated
	{
	public:
		CModuleRegInfoValidated(const CModuleRegInfo& info)
			: m_userProvided(info)
		{
		}
		//void Validate();
		//void Init(const CModuleInfo& info);

		Niflect::CString m_typeRegBasePath;
		Niflect::CString m_moduleRegBasePath;
		CModuleRegInfo m_userProvided;
	};
}