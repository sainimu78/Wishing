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
    bool create_directory(const Niflect::CString& path) {
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
        // 获取文件路径的目录部分
        std::string::size_type pos = file_path.find_last_of("/\\");
        if (pos != std::string::npos) {
            auto dir = file_path.substr(0, pos);

            // 分割路径并逐层创建目录
            Niflect::TArrayNif<Niflect::CString> path_segments;
            Niflect::CString current_path;
            for (char ch : dir) {
                if (ch == '/' || ch == '\\') {
                    if (!current_path.empty()) {
                        path_segments.push_back(current_path);
                        current_path.clear();
                    }
                }
                else {
                    current_path += ch;
                }
            }
            if (!current_path.empty()) {
                path_segments.push_back(current_path);
            }

            // 创建每一层目录
            Niflect::CString constructed_path;
            for (const auto& segment : path_segments) {
                constructed_path += segment + "/";
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
                delete_directory(full_path);
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
}