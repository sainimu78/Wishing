#pragma once
#include "Niflect/NiflectCommon.h"
#include "Niflect/Memory/Stats/NiflectMemoryStats.h"

namespace Niflect
{
	class CDefaultMemory
	{
	public:
		NIFLECT_API static void* Alloc(size_t size);
		NIFLECT_API static void* Realloc(void* ptr, size_t size);
		NIFLECT_API static void Free(void* ptr);
	};

	class CDefaultMemoryStatsScope
	{
	public:
		CDefaultMemoryStatsScope()
		{
			Begin();
		}
		~CDefaultMemoryStatsScope()
		{
			End();
		}

	private:
		NIFLECT_API static void Begin();
		NIFLECT_API static void End();
	};

	NIFLECT_API CMemoryStats* GetDefaultMemoryStats();

	NIFLECT_API void TestMemoryStatsOnThreadsBegin();
	NIFLECT_API void TestMemoryStatsOnThreadsEnd();
}