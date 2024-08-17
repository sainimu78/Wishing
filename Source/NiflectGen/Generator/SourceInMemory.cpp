#include "NiflectGen/Generator/SourceInMemory.h"
#include "clang-c/Index.h"

namespace NiflectGen
{
	using namespace Niflect;

	void CSourceInMemory::FillData(CXUnsavedFile* handle) const
	{
		handle->Filename = m_filePath.data();
		handle->Contents = m_data.data();
		handle->Length = static_cast<uint32>(m_data.length());
	}
}