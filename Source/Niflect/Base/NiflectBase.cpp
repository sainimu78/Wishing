#include "Niflect/Base/NiflectBase.h"

namespace Niflect
{
	IAllocatorInterface* CMemory::s_currentAllocator = NULL;

	void* CMemory::Alloc(size_t size)
	{
		if (s_currentAllocator == NULL)
			return CDefaultMemory::Alloc(size);
		return s_currentAllocator->Alloc(size);
	}
	void* CMemory::Realloc(void* ptr, size_t size)
	{
		if (s_currentAllocator == NULL)
			return CDefaultMemory::Realloc(ptr, size);
		return s_currentAllocator->Realloc(ptr, size);
	}
	void CMemory::Free(void* ptr)
	{
		if (s_currentAllocator == NULL)
		{
			CDefaultMemory::Free(ptr);
			return;
		}
		s_currentAllocator->Free(ptr);
	}
	void CMemory::SetCurrentAllocator(IAllocatorInterface* p)
	{
		ASSERT(p == NULL || s_currentAllocator == NULL);
		s_currentAllocator = p;
	}
}