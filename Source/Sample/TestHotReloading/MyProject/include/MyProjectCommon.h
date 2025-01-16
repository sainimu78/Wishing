#pragma once

#ifdef MYPROJECT_API
#else
#ifdef WIN32
#ifdef MYPROJECT_EXPORTS
#define MYPROJECT_API __declspec(dllexport)
#else
#define MYPROJECT_API __declspec(dllimport)
#endif
#else
#ifdef MYPROJECT_EXPORTS
#define MYPROJECT_API __attribute__((visibility("default")))
#else
#define MYPROJECT_API 
#endif
#endif
#endif