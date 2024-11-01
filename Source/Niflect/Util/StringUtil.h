#pragma once
#include "Niflect/NiflectBase.h"
#include <stdarg.h>
#include <fstream>

namespace NiflectUtil
{
	static Niflect::CString FormatString(const char* format, ...)
	{
		char szContent[10240] = "";
		va_list va_alist;
		va_start(va_alist, format);
		vsnprintf(szContent, 10240, format, va_alist);
		va_end(va_alist);
		return szContent;
	}
	static std::string FormatStdString(const char* format, ...)
	{
		char szContent[10240] = "";
		va_list va_alist;
		va_start(va_alist, format);
		vsnprintf(szContent, 10240, format, va_alist);
		va_end(va_alist);
		return szContent;
	}
	static float StringToFloat(const Niflect::CString& str)
	{
        return static_cast<float>(atof(str.c_str()));
	}
	static bool StartsWith(const Niflect::CString& fullString, const Niflect::CString& start)
	{
		if (fullString.length() >= start.length())
		{
			return (0 == fullString.compare(0, start.length(), start));
		}
		return false;
	}
	static bool EndsWith(const Niflect::CString& fullString, const char& ending)
	{
		if (fullString.length() >= 1)
			return fullString.back() == ending;
		return false;
	}
	static bool EndsWith(const Niflect::CString& fullString, const Niflect::CString& ending)
	{
		if(fullString.length() >= ending.length())
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		return false;
	}
	static Niflect::CString ReplaceFilePathExt(const Niflect::CString& filePath, const Niflect::CString& a, const Niflect::CString& b)
	{
		auto pos = filePath.find_last_of(a);
		if (pos != std::string::npos)
		{
			auto result = filePath.substr(0, pos - 1);
			result += b;
			return result;
		}
		return filePath;
	}
	static Niflect::CString RemoveFileExt(const Niflect::CString& filePath, const Niflect::CString& ext = ".")
	{
		auto pos = filePath.find_last_of(ext);
		if (pos != std::string::npos)
		{
			auto result = filePath.substr(0, pos);
			return result;
		}
		return filePath;
	}
	static Niflect::CString ConcatPath(const Niflect::CString& a, const Niflect::CString& b)
	{
		return a + "/" + b;
	}
	static bool GetParentDirPathSafe(const Niflect::CString& fileOrDirPath, Niflect::CString& parentDirPath)
	{
		auto posSlash = fileOrDirPath.find_last_of('/');
		if (posSlash != std::string::npos)
		{
			parentDirPath = fileOrDirPath.substr(0, fileOrDirPath.length() - posSlash - 1);
			return true;
		}
		return false;
	}
	static Niflect::CString GetParentDirPath(const Niflect::CString& fileOrDirPath)
	{
		Niflect::CString parentDirPath;
		if (GetParentDirPathSafe(fileOrDirPath, parentDirPath))
			return parentDirPath;
		return fileOrDirPath;
	}
	static Niflect::CString GetFileName(const Niflect::CString& filePath)
	{
		auto posSlash = filePath.find_last_of('/');
		if (posSlash != std::string::npos)
			return filePath.substr(posSlash + 1, filePath.length() - posSlash);
		return filePath;
	}
	static Niflect::CString GetDirName(const Niflect::CString& dirPath)
	{
		return GetFileName(dirPath);
	}
	static void WriteStringToFile(const Niflect::CString& data, const Niflect::CString& filePath)
	{
		std::ofstream ofs(filePath.c_str(), std::ios::binary);
		ASSERT(ofs.is_open());
		ofs << data;
		ofs.close();
	}
	static Niflect::CString ReadStringFromFile(const Niflect::CString& filePath)
	{
		std::ifstream ifs(filePath.c_str(), std::ios::binary);
		char buffer[1024];
		Niflect::CString data;
		while (ifs.read(buffer, sizeof(buffer)))
			data.append(buffer, ifs.gcount());
		data.append(buffer, ifs.gcount());
		return data;
	}
}