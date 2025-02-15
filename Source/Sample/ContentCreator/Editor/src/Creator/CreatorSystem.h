#pragma once
#include "Creator/CreatorOption.h"
#include "Base/BoostWrapper.h"
#include "Content/ContentManager.h"
#include "qobject.h"
#include "EditorDevelopmentMacro.h"//避免 moc 不能获取到其中的宏定义导致可能的解析错误. 此显式 include 避免错误的方法仅当被 PCH 中宏包围且指定 Q_OBJECT 的类出现时使用, 或遇 moc 代码相关的链接错误出现时相应 include PCH 头文件, 需要注意的是, 当包围相应类的宏不定义时, 需要注释或移除相应的 PCH include, 否则出现 moc 代码相关错误

namespace Wishing
{
	class CFoundModuleInfo
	{
	public:
		Niflect::CString m_filePath;
		Niflect::CString m_name;
		Niflect::CString m_getInfoFuncName;
	};

	class CCreatorPipeline
	{
		class CThreadSafeState
		{
		public:
			CThreadSafeState()
				: m_running(false)
			{
			}
			boost::mutex& GetMutex();
			bool m_running;
			CSharedBoostMutex m_mtx;
		};
	public:
		void Clear();

	public:
		CThreadSafeState m_state;
		CSharedBoostConditionVariable m_cv;
#ifdef PIPELINE_RUNNING_WITH_IO_CONTEXT
		CSharedBoostIoContext m_ctx;
#endif
		CSharedBoostThread m_thread;
	};

#ifdef PIPELINE_MAIN_THREAD_SYNC_CALLBACK
	class QtMainThreadExecutor : public QObject {
		Q_OBJECT
	public:
		QtMainThreadExecutor()
		{
			QObject::connect(this, &QtMainThreadExecutor::workFinished, [this]()
				{
					m_task();
				});
		}
		void post(const std::function<void()>& task) {
			m_task = task;
			QMetaObject::invokeMethod(this, "workFinished", Qt::QueuedConnection);
		}

	signals:
		void workFinished();

	private:
		std::function<void()> m_task;
	};
#endif

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
		void AsyncActivate();

	private:
		void AsyncRun();
#ifdef PIPELINE_RUNNING_WITH_IO_CONTEXT
		void AsyncRun2();
		void AsyncWaitReaction();
#endif

#ifdef CPP_SCRIPT_HOT_RELOADING_EXPERIMENT
	public:
		void ReloadScript();

	private:
		void FindProject();
#endif
	public:
		CContentManager& GetContentManager() { return m_contentMgr; }

	private:
		CCreatorOption m_opt;
#ifdef CPP_SCRIPT_HOT_RELOADING_EXPERIMENT
		Niflect::TArray<CFoundModuleInfo> m_vecFoundModuleInfo;
		uint32 m_loadingCounter;
#endif
		CCreatorPipeline m_pipeline;
		uint32 m_pipelineActivatedCount;
		CContentManager m_contentMgr;
#ifdef PIPELINE_MAIN_THREAD_SYNC_CALLBACK
		QtMainThreadExecutor m_a;
#endif
	};
}