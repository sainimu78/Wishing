#pragma once
#include "Creator/CreatorOption.h"
#include "Base/BoostWrapper.h"
#include "Content/ContentManager.h"
#include "qobject.h"

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

	class QtMainThreadExecutor : public QObject {
		Q_OBJECT
	public:
		void post(std::function<void()> task) {
			QObject::connect(this, &QtMainThreadExecutor::workFinished, [task]()
				{
					task();
				});
			QMetaObject::invokeMethod(this, "workFinished", Qt::QueuedConnection);
		}

	signals:
		void workFinished();
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
		QtMainThreadExecutor m_a;
	};
}