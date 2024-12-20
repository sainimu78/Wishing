#pragma once
#include "Niflect/NiflectBase.h"
#include "Niflect/NiflectCommon.h"

namespace NiflectUtil
{
	NIFLECT_API void MakeDirectories(const Niflect::CString& file_path);
	NIFLECT_API bool DeleteDirectory(const Niflect::CString& dir);
	NIFLECT_API bool DirectoryExists(const Niflect::CString& dir);
	NIFLECT_API bool FileExists(const Niflect::CString& path);
	NIFLECT_API Niflect::CString GetCurrentWorkingDirPath();
	NIFLECT_API Niflect::CString ResolvePath(const Niflect::CString& relativePath);
	NIFLECT_API void SearchFiles(const Niflect::CString& dirPath, const Niflect::CString& pattern, Niflect::TArrayNif<Niflect::CString>& vecFound);
}