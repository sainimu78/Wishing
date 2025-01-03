#pragma once

#ifdef SAMPLEAPI_API
#else
#ifdef WIN32
#ifdef SAMPLEAPI_EXPORTS
#define SAMPLEAPI_API __declspec(dllexport)
#else
#define SAMPLEAPI_API __declspec(dllimport)
#endif
#else
#ifdef SAMPLEAPI_EXPORTS
#define SAMPLEAPI_API __attribute__((visibility("default")))
#else
#define SAMPLEAPI_API 
#endif
#endif
#endif