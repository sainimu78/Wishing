#include "Creator/CreatorSystem.h"
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Util/SystemUtil.h"
#include "Niflect/NiflectModule.h"
#include "Script.h"
#include "Niflect/Memory/Default/DefaultMemory.h"

#include <Windows.h>

namespace Wishing
{
	CCreatorSystem::CCreatorSystem()
		: m_loadingCounter(0)
	{

	}
	bool CCreatorSystem::Initialize(const CCreatorOption& opt)
	{
		m_opt = opt;
		this->FindProject();
		return true;
	}
	bool CCreatorSystem::Start()
	{
		for (auto& it : m_vecFoundModuleInfo)
			printf("Found module: %s\n", it.m_name.c_str());
		
		return false;
	}
	bool CCreatorSystem::Stop()
	{
		return false;
	}
	bool CCreatorSystem::Finalize()
	{
		return false;
	}
	void CCreatorSystem::FindProject()
	{
		ASSERT(!m_opt.m_projectDirPath.empty());

		Niflect::TArray<Niflect::CString> vecModuleFilePath;
		const char* pszRelativeModuleDirPath = "Windows/DefaultBuild/Debug/bin";
		//const char* pszRelativeModuleDirPath = "Windows/DefaultBuild/Installed/TestHotReloading/build/Windows/x64/Debug/bin";
		auto maybeModuleDirPath = NiflectUtil::ConcatPath(m_opt.m_projectDirPath, pszRelativeModuleDirPath);
		using namespace NiflectUtil;
		NiflectUtil::CollectFiles(maybeModuleDirPath, CCollectingOption([&maybeModuleDirPath, &vecModuleFilePath](const SCollectingContext& ctx)
			{
				if (NiflectUtil::EndsWith(ctx.m_fileName, ".dll"))
				{
					auto absDirPath = NiflectUtil::ConcatPath(maybeModuleDirPath, ctx.m_dirPath);
					vecModuleFilePath.push_back(NiflectUtil::ConcatPath(absDirPath, ctx.m_fileName));
				}
			}));
		for (auto& it : vecModuleFilePath)
		{
			auto moduleHandle = LoadLibrary(it.c_str());
			if (moduleHandle != NULL)
			{
				auto fileName = NiflectUtil::GetFileName(it);
				auto pos = fileName.find('.');
				ASSERT(pos != std::string::npos);
				auto moduleName = fileName.substr(0, pos);
				auto getInfoFuncName = Niflect::GetGeneratedGetModuleInfoFuncName(moduleName);
				auto Func = reinterpret_cast<Niflect::GeneratedGetModuleInfoFunc>(GetProcAddress(moduleHandle, getInfoFuncName.c_str()));
				if (Func != NULL)
				{
					CFoundModuleInfo info;
					info.m_name = moduleName;
					info.m_filePath = it;
					info.m_getInfoFuncName = getInfoFuncName;
					m_vecFoundModuleInfo.push_back(info);
				}
			}
			FreeLibrary(moduleHandle);
		}
	}
	void CCreatorSystem::ReloadScript()
	{
		Niflect::CDefaultMemoryStatsScope scope;
		auto memTest = Niflect::GetDefaultMemoryStats();
		
		ASSERT(m_vecFoundModuleInfo.size() == 1);
		auto& foundInfo = m_vecFoundModuleInfo[0];

		auto moduleFilePath = foundInfo.m_filePath;

		//if (m_loadingCounter > 0)
		//{
		//	auto fileExt = NiflectUtil::GetFileExt(moduleFilePath);
		//	moduleFilePath = NiflectUtil::ReplaceFilePathExt(moduleFilePath, fileExt, NiflectUtil::FormatString("_%u%s", m_loadingCounter, fileExt.c_str()));
		//}
		//printf("Try to load: %s\n", moduleFilePath.c_str());

		auto moduleHandle = LoadLibrary(moduleFilePath.c_str());
		if (moduleHandle != NULL)
		{
			auto Func = reinterpret_cast<Niflect::GeneratedGetModuleInfoFunc>(GetProcAddress(moduleHandle, foundInfo.m_getInfoFuncName.c_str()));
			auto info = Func();
			info->RegisterTypes();
			info->InitTypes();
			info->InitTableTypesLayout();

			auto table = info->GetTable();
			if (auto type = table->FindTypeByTypeName("CPanel"))
			{
				auto script = type->MakeSharedInstance<Wishing::CScript>();
				script->Execute();
			}
			else
			{
				ASSERT(false);
			}
			FreeLibrary(moduleHandle);
		}
		else
		{
			ASSERT(false);
		}

		m_loadingCounter++;
		printf("Reload count: %u\n", m_loadingCounter);
	}
}