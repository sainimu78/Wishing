#include "NiflectGen/Generator/SourceInMemory.h"
#include "clang-c/Index.h"

namespace NiflectGen
{
	CXUnsavedFile CSourceInMemory::GetCXUnsavedFileHandle() const
	{
		CXUnsavedFile handle;
		handle.Filename = m_filePath.data();
		handle.Contents = m_data.data();
		handle.Length = static_cast<uint32>(m_data.length());
		return handle;
	}
}