#pragma once
#include "Niflect/NiflectCommon.h"

namespace Niflect
{
	class CMemory
	{
	public:
		NIFLECT_API static void* Alloc(size_t size);
		NIFLECT_API static void* Realloc(void* ptr, size_t size);
		NIFLECT_API static void Free(void* ptr);
	};
	
	class CMemoryStatsScope
	{
	public:
		CMemoryStatsScope();
		~CMemoryStatsScope();

	public:
		static void Begin();
		static void End();
	};

	void MyThreadTest();

	class CMemoryStats;
	NIFLECT_API CMemoryStats* DebugGetMemoryStats();
}