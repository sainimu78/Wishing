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

	void TestMemoryStatsOnThreads();

	class CMemoryStats;
	NIFLECT_API CMemoryStats* DebugGetMemoryStats();
}

//begin
//todo: 此实验表明, 可定义一种threadlocal的全局allocatorScope, 通过不同的Scope配置当前DefaultMemory的行为 
//class CMyClassForSimplifiedMakeShared
//{
//public:
//	CMyClassForSimplifiedMakeShared()
//		: m_float(1.23f)
//		, m_bool(true)
//		, m_double(43.21)
//	{
//
//	}
//	float m_float;
//	bool m_bool;
//	double m_double;
//};
//
//class CMyPooledMemoryScope
//{
//public:
//	CMyPooledMemoryScope();
//	~CMyPooledMemoryScope();
//	void* Alloc(size_t size)
//	{
//		m_poolSize += size;
//		m_poolMem = Niflect::CMemory::Realloc(m_poolMem, m_poolSize);
//		return m_poolMem;
//	}
//	void* Realloc(void* ptr, size_t size)
//	{
//		return this->Alloc(size);
//	}
//	void Free(void* ptr)
//	{
//	}
//	size_t m_poolSize;
//	void* m_poolMem;
//};
//
//class CMyMemory
//{
//public:
//	static void* Alloc(size_t size)
//	{
//		return g_currentAllocator->Alloc(size);
//	}
//	static void* Realloc(void* ptr, size_t size)
//	{
//		return g_currentAllocator->Realloc(ptr, size);
//	}
//	static void Free(void* ptr)
//	{
//		g_currentAllocator->Free(ptr);
//	}
//	static CMyPooledMemoryScope* g_currentAllocator;
//};
//
//CMyPooledMemoryScope* CMyMemory::g_currentAllocator = NULL;
//
//CMyPooledMemoryScope::CMyPooledMemoryScope()
//	: m_poolSize(0)
//	, m_poolMem(NULL)
//{
//	//需要考虑嵌套的情况?
//	CMyMemory::g_currentAllocator = this;
//}
//CMyPooledMemoryScope::~CMyPooledMemoryScope()
//{
//	CMyMemory::g_currentAllocator = NULL;
//	Niflect::CMemory::Free(m_poolMem);
//}
//end
