#pragma once
#include "Niflect/Base/SharedPtr.h"

namespace boost
{
	class thread;
	class mutex;
	class condition_variable;
}

namespace Wishing
{
	using CSharedBoostThread = Niflect::TSharedPtr<boost::thread>;
	using CSharedBoostMutex = Niflect::TSharedPtr<boost::mutex>;
	using CSharedBoostConditionVariable = Niflect::TSharedPtr<boost::condition_variable>;
}