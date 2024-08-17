#pragma once
#include "Niflect/NiflectBase.h"

struct CXUnsavedFile;

namespace NiflectGen
{
	class CSourceInMemory
	{
	public:
		void FillData(CXUnsavedFile* handle) const;

	public:
		Niflect::CString m_filePath;
		Niflect::CString m_data;
	};
}