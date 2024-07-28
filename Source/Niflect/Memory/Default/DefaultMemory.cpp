#include "Niflect/Memory/Default/DefaultMemory.h"
#include "Niflect/Memory/Generic/GenericMemory.h"
#include "Niflect/Memory/Generic/GenericSharedPtr.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

namespace Niflect
{
	thread_local CMemoryStats* g_memoryStatsThreadLocal = NULL;
	
	void CMemoryStatsScope::Begin()
	{
		ASSERT(g_memoryStatsThreadLocal == NULL);
		g_memoryStatsThreadLocal = new CMemoryStats;
	}
	void CMemoryStatsScope::End()
	{
		delete g_memoryStatsThreadLocal;
		g_memoryStatsThreadLocal = NULL;
	}
	CMemoryStatsScope::CMemoryStatsScope()
	{
		Begin();
	}
	CMemoryStatsScope::~CMemoryStatsScope()
	{
		End();
	}
	
	std::mutex g_mtxPrint;
	void threadFunction()
	{
		CMemoryStatsScope memStatsScope;

		auto memTest = DebugGetMemoryStats();
		std::lock_guard<std::mutex> lg(g_mtxPrint);
		std::cout << memTest << std::endl;
	}

	void TestMemoryStatsOnThreads()
	{
		std::vector<std::thread> threads;
		for (int i = 0; i < 5; ++i)
		{
			threads.emplace_back(threadFunction);
		}

		for (auto& t : threads)
		{
			t.join();
		}
	}

	static const bool g_enabledMemoryStats_MainThreadOnly_IncludingStaticStage = false;

	static void MakeSureInitMemoryStats()
	{
		if (!g_enabledMemoryStats_MainThreadOnly_IncludingStaticStage)
			return;
		if (g_memoryStatsThreadLocal == NULL)
		{
			static CMemoryStats s_holder;
			g_memoryStatsThreadLocal = &s_holder;
		}
	}
	
	void* CMemory::Alloc(size_t size)
	{
		MakeSureInitMemoryStats();
		return CGenericMemory::Alloc(size, g_memoryStatsThreadLocal);
	}
	void* CMemory::Realloc(void* ptr, size_t size)
	{
		MakeSureInitMemoryStats();
		return CGenericMemory::Realloc(ptr, size, g_memoryStatsThreadLocal);
	}
	void CMemory::Free(void* ptr)
	{
		CGenericMemory::Free(ptr, g_memoryStatsThreadLocal);
	}
	
	CMemoryStats* DebugGetMemoryStats()
	{
		MakeSureInitMemoryStats();
		return g_memoryStatsThreadLocal;
	}
	
	static void TestReserved()
	{
		auto memoryTest = g_memoryStatsThreadLocal;
		auto p0 = CMemory::Alloc(4);
		ASSERT((memoryTest = g_memoryStatsThreadLocal)->m_allocatedBytesRuntimeTotal == 4);
		auto p1 = CMemory::Alloc(6);
		ASSERT((memoryTest = g_memoryStatsThreadLocal)->m_allocatedBytesRuntimeTotal == 10);
		p0 = CMemory::Realloc(p0, 6);
		ASSERT((memoryTest = g_memoryStatsThreadLocal)->m_allocatedBytesRuntimeTotal == 12);
		p1 = CMemory::Realloc(p1, 4);
		ASSERT(((memoryTest = g_memoryStatsThreadLocal)->m_allocatedBytesRuntimeTotal == 12) && ((memoryTest = g_memoryStatsThreadLocal)->m_freedBytesRuntimeTotal == 2));
		auto p2 = CMemory::Alloc(3);
		ASSERT((memoryTest = g_memoryStatsThreadLocal)->m_allocatedBytesRuntimeTotal == 15);
		CMemory::Free(p0);
		ASSERT((memoryTest = g_memoryStatsThreadLocal)->m_freedBytesRuntimeTotal == 8);
		CMemory::Free(p1);
		ASSERT((memoryTest = g_memoryStatsThreadLocal)->m_freedBytesRuntimeTotal == 12);
		CMemory::Free(p2);
		auto expectedBytesCount = 3*sizeof(size_t) + 6 + 4 + 3 + 2;//sizeof(size_t)表示每块分配的内存信息头字节数; 6, 4, 3分别为p0, p1, p2释放之前的字节数; 2为p1从6 Realloc为4后, 逻辑上被释放的字节数
		ASSERT(((memoryTest = g_memoryStatsThreadLocal)->m_freedBytesRuntimeTotal == 15) && ((memoryTest = g_memoryStatsThreadLocal)->m_freeCount == 3) && ((memoryTest = g_memoryStatsThreadLocal)->m_freedBytesTotal == expectedBytesCount));
	}
}