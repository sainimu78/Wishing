#pragma once
#include "Creator/CreatorOption.h"

namespace Wishing
{
	class CFoundModuleInfo
	{
	public:
		Niflect::CString m_filePath;
		Niflect::CString m_name;
		Niflect::CString m_getInfoFuncName;
	};

	class CCreatorSystem
	{
	public:
		CCreatorSystem();

	public:
		bool Initialize(const CCreatorOption& opt);
		bool Start();
		bool Stop();
		bool Finalize();

	public:
		void ReloadScript();

	private:
		void FindProject();

	private:
		CCreatorOption m_opt;
		Niflect::TArray<CFoundModuleInfo> m_vecFoundModuleInfo;
		uint32 m_loadingCounter;
	};
}