#include "Creator/CreatorSystem.h"
#include "boost/thread/thread.hpp"
#ifdef PIPELINE_RUNNING_WITH_IO_CONTEXT
#include "boost/asio/io_context.hpp"
#endif

#ifdef CPP_SCRIPT_HOT_RELOADING_EXPERIMENT
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Util/SystemUtil.h"
#include "Niflect/NiflectModule.h"
#include "Script.h"
#include "Niflect/Memory/Default/DefaultMemory.h"
#include <Windows.h>
#endif

#include "Niflect/Serialization/JsonFormat.h"
#include "Niflect/Util/FileStreamUtil.h"
#include "Base/AssetCreatorDefinition.h"
#include "Niflect/Util/StringUtil.h"

namespace Wishing
{
	boost::mutex& CCreatorPipeline::CThreadSafeState::GetMutex()
	{
		return *m_mtx;
	}
	void CCreatorPipeline::Clear()
	{
		*this = CCreatorPipeline();
	}

#ifdef CPP_SCRIPT_HOT_RELOADING_EXPERIMENT
	CCreatorSystem::CCreatorSystem()
		: m_loadingCounter(0)
	{

	}
#else
	CCreatorSystem::CCreatorSystem()
		: m_pipelineActivatedCount(0)
	{

	}
#endif
	bool CCreatorSystem::Initialize(const CCreatorOption& opt)
	{
		m_opt = opt;
#ifdef CPP_SCRIPT_HOT_RELOADING_EXPERIMENT
		this->FindProject();
#endif

		DebugPrintDirNodeRecurs(m_contentMgr.GetRootDirNode());
		{
			CContentChangeContext ctx;
			m_contentMgr.FindOrCreateFileNodePath("Nihao/Bucuo/a.txt", ctx);
			m_contentMgr.FindOrCreateFileNodePath("Nihao/Shi/b.txt", ctx);
			m_contentMgr.FindOrCreateFileNodePath("c.txt", ctx);
			m_contentMgr.FindOrCreateFileNodePath("Buxin/d.txt", ctx);

			for (auto& it : ctx.m_vecDeletingDirtyNode)
				printf("%s\n", it->GetName().c_str());
			for (auto& it : ctx.m_vecExistingDirtyNode)
				printf("%s\n", it->GetName().c_str());
		}
		{
			RwTree::CRwNode rw;
			m_contentMgr.Save(&rw);
			auto filePath = NiflectUtil::ConcatPath(AssetCreatorDefinition::DirPath::GetExampleAssetDirPath(), "a.txt");
			std::ofstream ofs;
			if (NiflectUtil::OpenFileStream(ofs, filePath))
				RwTree::CJsonFormat::Write(&rw, ofs);
		}
		DebugPrintDirNodeRecurs(m_contentMgr.GetRootDirNode());
		return true;
	}
	bool CCreatorSystem::Start()
	{
#ifdef CPP_SCRIPT_HOT_RELOADING_EXPERIMENT
		for (auto& it : m_vecFoundModuleInfo)
			printf("Found module: %s\n", it.m_name.c_str());
#endif

		ASSERT(m_pipeline.m_thread == NULL);
		bool ok = false;
		m_pipeline.m_cv = Niflect::MakeShared<boost::condition_variable>();
		m_pipeline.m_state.m_mtx = Niflect::MakeShared<boost::mutex>();
		m_pipeline.m_state.m_running = true;
#ifdef PIPELINE_RUNNING_WITH_IO_CONTEXT
		m_pipeline.m_ctx = Niflect::MakeShared<boost::asio::io_context>();
		m_pipeline.m_thread = Niflect::MakeShared<boost::thread>(&CCreatorSystem::AsyncRun2, this);
#else
		m_pipeline.m_thread = Niflect::MakeShared<boost::thread>(&CCreatorSystem::AsyncRun, this);
#endif
		ok = m_pipeline.m_thread != NULL;
		return ok;
	}
	bool CCreatorSystem::Stop()
	{
		{
			boost::lock_guard<boost::mutex> lock(m_pipeline.m_state.GetMutex());
			m_pipeline.m_state.m_running = false;
		}
		m_pipeline.m_cv->notify_all();
		m_pipeline.m_thread->join();
		m_pipeline.Clear();
		return true;
	}
	bool CCreatorSystem::Finalize()
	{
		return false;
	}
#ifdef CPP_SCRIPT_HOT_RELOADING_EXPERIMENT
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
#endif
	void CCreatorSystem::AsyncActivate()
	{
		m_pipeline.m_cv->notify_one();
	}
	void CCreatorSystem::AsyncRun()
	{
		while (true)
		{
			{
				boost::unique_lock<boost::mutex> lock(m_pipeline.m_state.GetMutex());
				m_pipeline.m_cv->wait(lock);
				if (!m_pipeline.m_state.m_running)
					break;
			}
			printf("Activated: %u\n", m_pipelineActivatedCount);
			boost::this_thread::sleep_for(boost::chrono::seconds(3));
			printf("Done\n");
			m_pipelineActivatedCount++;

			m_a.post([]()
				{
					printf("");
				});
			{
				boost::unique_lock<boost::mutex> lock(m_pipeline.m_state.GetMutex());
				if (!m_pipeline.m_state.m_running)
					break;
			}
		}
		printf("Finished\n");
	}
#ifdef PIPELINE_RUNNING_WITH_IO_CONTEXT
	void CCreatorSystem::AsyncRun2()
	{
		this->AsyncWaitReaction();
		m_pipeline.m_ctx->run();
	}
	void CCreatorSystem::AsyncWaitReaction()
	{
		m_pipeline.m_ctx->post([this]()
			{
				{
					boost::unique_lock<boost::mutex> lock(m_pipeline.m_state.GetMutex());
					m_pipeline.m_cv->wait(lock);
					if (!m_pipeline.m_state.m_running)
						return;
				}
				printf("Activated: %u\n", m_pipelineActivatedCount);
				boost::this_thread::sleep_for(boost::chrono::seconds(3));
				printf("Done\n");
				m_pipelineActivatedCount++;

				{
					boost::unique_lock<boost::mutex> lock(m_pipeline.m_state.GetMutex());
					if (!m_pipeline.m_state.m_running)
						return;
				}
				this->AsyncWaitReaction();
			});
	}
#endif
}
