#pragma once
#include "Niflect/NiflectBase.h"
#include "clang-c/Index.h"

namespace NiflectGen
{
	class CSourceInMemory
	{
	public:
		CXUnsavedFile GetCXUnsavedFileHandle() const;

	public:
		Niflect::CString m_filePath;
		Niflect::CString m_data;
	};
}