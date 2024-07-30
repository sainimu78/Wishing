#pragma once
#include "Niflect/NiflectCommon.h"

namespace Niflect
{
	class CDefaultMemory
	{
	public:
		NIFLECT_API static void* Alloc(size_t size);
		NIFLECT_API static void* Realloc(void* ptr, size_t size);
		NIFLECT_API static void Free(void* ptr);
	};
	
	class CMemoryStatsScope
	{
	public:
		CMemoryStatsScope()
		{
			Begin();
		}
		~CMemoryStatsScope()
		{
			End();
		}

	public:
		NIFLECT_API static void Begin();
		NIFLECT_API static void End();
	};

	NIFLECT_API void TestMemoryStatsOnThreadsBegin();
	NIFLECT_API void TestMemoryStatsOnThreadsEnd();

	class CMemoryStats;
	NIFLECT_API CMemoryStats* DebugGetMemoryStats();
}