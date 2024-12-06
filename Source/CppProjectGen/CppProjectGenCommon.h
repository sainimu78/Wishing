#pragma once

#ifdef CPPPROJECTGEN_API
#else
#ifdef WIN32
#ifdef CPPPROJECTGEN_EXPORTS
#define CPPPROJECTGEN_API __declspec(dllexport)
#else
#define CPPPROJECTGEN_API __declspec(dllimport)
#endif
#else
#ifdef CPPPROJECTGEN_EXPORTS
#define CPPPROJECTGEN_API __attribute__((visibility("default")))
#else
#define CPPPROJECTGEN_API 
#endif
#endif
#endif
