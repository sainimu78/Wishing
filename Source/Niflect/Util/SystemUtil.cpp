#include "Niflect/Util/SystemUtil.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <vector>

#ifdef _WIN32
#include <direct.h> // for _mkdir
#else
#include <sys/stat.h> // for mkdir
#endif

//#ifdef _WIN32
//#include <direct.h> // for _getcwd
//#define GETCWD _getcwd
//#include <Windows.h> // for MAX_PATH
//#define MY_PATH_MAX MAX_PATH
//#else
//#include <unistd.h> // for getcwd
//#include <limits.h>
//#define GETCWD getcwd
//#define MY_PATH_MAX PATH_MAX
//#endif

namespace NiflectUtil
{
    static bool create_directory(const Niflect::CString& path) {
        struct stat info;

        // 检查路径是否已存在
        if (stat(path.c_str(), &info) != 0) {
            // 路径不存在，尝试创建
#ifdef _WIN32
            if (_mkdir(path.c_str()) != 0) {
#else
            if (mkdir(path.c_str(), 0777) != 0) {
#endif
                std::cerr << "Error creating directory: " << path << std::endl;
                return false;
            }
            }
        else if (!(info.st_mode & S_IFDIR)) {
            // 路径存在但不是目录
            std::cerr << path << " exists but is not a directory." << std::endl;
            return false;
        }
        return true;
    }
    void MakeDirectories(const Niflect::CString& file_path)
    {
        std::string::size_type pos = file_path.find_last_of('/');
        if (pos != std::string::npos) {
            auto dir = file_path.substr(0, pos);

            Niflect::TArrayNif<Niflect::CString> path_segments;
            Niflect::CString current_path;
            for (char ch : dir) {
                if (ch == '/') {
                    if (!current_path.empty()) {
                        path_segments.push_back(current_path);
                        current_path.clear();
                    }
#ifdef _WIN32
#else
                    else
                    {
                        path_segments.push_back(current_path);
                    }
#endif
                }
                else {
                    current_path += ch;
                }
            }
            if (!current_path.empty()) {
                path_segments.push_back(current_path);
            }

            Niflect::CString constructed_path;
            for (const auto& segment : path_segments) {
                constructed_path += segment + '/';
                if (!create_directory(constructed_path)) {
                    std::cerr << "Failed to create path: " << constructed_path << std::endl;
                    return;
                }
            }
        }
    }

    //Niflect::CString GetCurrentWorkingDir()
    //{
    //    char buffer[MY_PATH_MAX];
    //    char* cwd = GETCWD(buffer, sizeof(buffer));

    //    Niflect::CString result;
    //    if (cwd) {
    //        result = cwd;
    //    }
    //    else {
    //        std::cerr << "Error getting current working directory." << std::endl;
    //    }

    //    return result;
    //}

//    bool RemoveDirectory(const std::string& dir_path) {
//#ifdef _WIN32
//        // Windows下使用 rmdir 命令
//        std::string command = "rmdir /s /q \"" + dir_path + "\"";
//#else
//        // Unix/Linux/Mac下使用 rm -rf 命令
//        std::string command = "rm -rf \"" + dir_path + "\"";
//#endif
//
//        int result = std::system(command.c_str());
//        if (result == 0) {
//            //std::cout << "Directory removed successfully: " << dir_path << std::endl;
//            return true;
//        }
//        //std::cerr << "Error removing directory: " << dir_path << std::endl;
//        return false;
//    }
}

#ifdef _WIN32
#include <windows.h>
#include <algorithm>
#else
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace NiflectUtil
{
    bool DeleteDirectory(const Niflect::CString& dir) {
        if (dir.empty())
            return false;
#ifdef _WIN32
        WIN32_FIND_DATA fileData;
        HANDLE hFind;

        // Append a wildcard to find all files and directories
        auto search_path = dir + "\\*";
        hFind = FindFirstFile(search_path.c_str(), &fileData);

        if (hFind == INVALID_HANDLE_VALUE) {
            return false;  // Failed to open directory
        }

        do {
            const Niflect::CString filename = fileData.cFileName;

            // Skip the special entries "." and ".."
            if (filename == "." || filename == "..") {
                continue;
            }

            const auto full_path = dir + "\\" + filename;

            if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // Recursively delete subdirectory
                DeleteDirectory(full_path);
                RemoveDirectory(full_path.c_str());
            }
            else {
                // Delete file
                DeleteFile(full_path.c_str());
            }
        } while (FindNextFile(hFind, &fileData) != 0);

        FindClose(hFind);
        return RemoveDirectory(dir.c_str());
#else
        DIR* directory = opendir(dir.c_str());
        if (!directory) {
            return false; // Failed to open directory
        }

        struct dirent* entry;
        while ((entry = readdir(directory)) != nullptr) {
            const Niflect::CString filename = entry->d_name;

            // Skip the special entries "." and ".."
            if (filename == "." || filename == "..") {
                continue;
            }

            const Niflect::CString full_path = dir + "/" + filename;

            if (entry->d_type == DT_DIR) {
                // Recursively delete subdirectory
                DeleteDirectory(full_path);
                rmdir(full_path.c_str());
            }
            else {
                // Delete file
                remove(full_path.c_str());
            }
        }

        closedir(directory);
        return rmdir(dir.c_str()) == 0;
#endif
    }

    bool DirectoryExists(const Niflect::CString& dir) {
#ifdef _WIN32
        DWORD dwAttrib = GetFileAttributes(dir.c_str());
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#else
        struct stat info;
        return (stat(dir.c_str(), &info) == 0 && (info.st_mode & S_IFDIR));
#endif
    }

    bool FileExists(const Niflect::CString& path) {
#ifdef _WIN32
        DWORD attributes = GetFileAttributes(path.c_str());
        return (attributes != INVALID_FILE_ATTRIBUTES);
#else
        struct stat buffer;
        return (stat(path.c_str(), &buffer) == 0);
#endif
    }

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

    Niflect::CString GetCurrentWorkingDirPath() {
#ifdef _WIN32
        char buffer[MAX_PATH];
        GetCurrentDirectoryA(MAX_PATH, buffer);
        Niflect::CString result(buffer);
        std::replace(result.begin(), result.end(), '\\', '/');
        return result;
#else
        char buffer[PATH_MAX];
        getcwd(buffer, sizeof(buffer));
        return Niflect::CString(buffer);
#endif
    }
    //bool ResolvePath(const Niflect::CString& relativePath, Niflect::CString& absolutePath) {
    //    auto currentPath = GetCurrentWorkingDirPath();
    //    Niflect::TArrayNif<Niflect::CString> parts;

    //    // 将当前路径分割成部分
    //    size_t start = 0;
    //    size_t end = currentPath.find('/');

    //    while (end != std::string::npos) {
    //        parts.push_back(currentPath.substr(start, end - start));
    //        start = end + 1;
    //        end = currentPath.find('/', start);
    //    }

    //    // 处理最后的部分
    //    parts.push_back(currentPath.substr(start));

    //    // 解析相对路径
    //    start = 0;
    //    end = relativePath.find('/');

    //    while (end != std::string::npos) {
    //        auto  token = relativePath.substr(start, end - start);
    //        if (token == "..") {
    //            // 上层目录，移除当前目录的最后部分
    //            if (!parts.empty()) {
    //                parts.pop_back();
    //            }
    //        }
    //        else if (token != "." && !token.empty()) {
    //            // 当前目录或非空部分，添加到路径
    //            parts.push_back(token);
    //        }
    //        start = end + 1;
    //        end = relativePath.find('/', start);
    //    }

    //    // 处理最后的部分
    //    Niflect::CString token = relativePath.substr(start);
    //    if (token == "..") {
    //        if (!parts.empty()) {
    //            parts.pop_back();
    //        }
    //    }
    //    else if (token != "." && !token.empty()) {
    //        parts.push_back(token);
    //    }

    //    // 组合成绝对路径
    //    for (const auto& part : parts) {
    //        absolutePath += part + '/';
    //    }

    //    // 去掉最后的斜杠
    //    if (!absolutePath.empty()) {
    //        absolutePath.pop_back();
    //    }

    //    ASSERT(false);//该函数预留仅处理含 ../ 的路径, 现未使用, 实际使用时应充分测试, 并相应改写
    //    return true;
    //}


#ifdef _WIN32
#include <windows.h>
#define PATH_MAX MAX_PATH
#else
#include <unistd.h>
#include <limits.h>
#endif

    static bool isRelativePath(const Niflect::CString& path) {
        // 检查路径是否以 /^ 或者 是当前目录 (./) 或者 ../ 开头。
        return !(path.empty() || path[0] == '/' || (path.length() > 1 && path[1] == ':'));
    }

#ifdef TEST_ConvertToAbsolutePath
    static void TestConvertToAbsolutePath()
    {
        auto cw = NiflectUtil::GetCurrentWorkingDirPath();//F:/Fts/Proj/Test/aaaaaaaaa/Build
        auto cwUpper = NiflectUtil::GetParentDirPath(cw);//F:/Fts/Proj/Test/aaaaaaaaa
        Niflect::CString expected0(NiflectUtil::ConcatPath(cwUpper, "MyClass.h"));//F:/Fts/Proj/Test/aaaaaaaaa/MyClass.h
        Niflect::CString expected1(NiflectUtil::ConcatPath(cwUpper, "Build/MyClass.h"));//F:/Fts/Proj/Test/aaaaaaaaa/Build/MyClass.h
        auto a = NiflectUtil::ConvertToAbsolutePath("../MyClass.h");
        ASSERT(a == expected0);
        auto b = NiflectUtil::ConvertToAbsolutePath(expected0);
        ASSERT(b == expected0);
        auto c = NiflectUtil::ConvertToAbsolutePath("MyClass.h");
        ASSERT(c == expected1);
        auto d = NiflectUtil::ConvertToAbsolutePath("./MyClass.h");
        ASSERT(d == expected1);
        auto e = NiflectUtil::ConvertToAbsolutePath("F:/Fts/Proj/Test/aaaaaaaaa/../../Test/aaaaaaaaa/MyClass.h");
        ASSERT(e == expected0);
    }
#endif

    Niflect::CString ConvertToAbsolutePath(const Niflect::CString& relativePath) {
        char absolutePath[PATH_MAX];  // POSIX 系统上使用 PATH_MAX。
#ifdef _WIN32
        // Windows 系统
        if (_fullpath(absolutePath, relativePath.c_str(), sizeof(absolutePath)) == nullptr) {
            throw std::runtime_error("Failed to convert to absolute path");
        }
        Niflect::CString result(absolutePath);
        std::replace(result.begin(), result.end(), '\\', '/');
        return result;
#else
        // POSIX 系统
        if (realpath(relativePath.c_str(), absolutePath) == nullptr) {
            throw std::runtime_error("Failed to convert to absolute path");
        }
        return Niflect::CString(absolutePath);
#endif
    }
}
