#pragma once

#ifdef WISHINGENGINE_API
#else
#ifdef WIN32
#ifdef WISHINGENGINE_EXPORTS
#define WISHINGENGINE_API __declspec(dllexport)
#else
#define WISHINGENGINE_API __declspec(dllimport)
#endif
#else
#ifdef WISHINGENGINE_EXPORTS
#define WISHINGENGINE_API __attribute__((visibility("default")))
#else
#define WISHINGENGINE_API 
#endif
#endif
#endif
