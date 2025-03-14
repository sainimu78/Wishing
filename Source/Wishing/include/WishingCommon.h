#pragma once

#ifdef WISHING_API
#else
#ifdef WIN32
#ifdef WISHING_EXPORTS
#define WISHING_API __declspec(dllexport)
#else
#define WISHING_API __declspec(dllimport)
#endif
#else
#ifdef WISHING_EXPORTS
#define WISHING_API __attribute__((visibility("default")))
#else
#define WISHING_API 
#endif
#endif
#endif
