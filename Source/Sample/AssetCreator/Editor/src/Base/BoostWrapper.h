#pragma once
#include "Niflect/Base/SharedPtr.h"

namespace boost
{
	class thread;
	class mutex;
	class condition_variable;
#ifdef PIPELINE_RUNNING_WITH_IO_CONTEXT
	namespace asio
	{
		class io_context;
	}
#endif
}

namespace Wishing
{
	using CSharedBoostThread = Niflect::TSharedPtr<boost::thread>;
	using CSharedBoostMutex = Niflect::TSharedPtr<boost::mutex>;
	using CSharedBoostConditionVariable = Niflect::TSharedPtr<boost::condition_variable>;
#ifdef PIPELINE_RUNNING_WITH_IO_CONTEXT
	using CSharedBoostIoContext = Niflect::TSharedPtr<boost::asio::io_context>;
#endif
}