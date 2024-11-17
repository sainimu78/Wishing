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
	//NIFLECT_API bool ResolvePath(const Niflect::CString& relativePath, Niflect::CString& absolutePath);
	NIFLECT_API Niflect::CString ConvertToAbsolutePath(const Niflect::CString& relativePath);
}