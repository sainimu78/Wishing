#pragma once
#include <cassert>
#include <cstddef>//std::size_t, offsetof
#include "IndexingConst.h"

//公共define, typedef, const

#ifndef ASSERT
enum { INDEX_NONE = tq::INDEX_NONE };

//begin, 实验阶段不使用PCH, 因此临时类型定义
typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef long long int64;
typedef unsigned int uint32;
typedef unsigned long long uint64;
//end

#define ASSERT(b) assert(b)
#endif

#ifndef LogError
#define LogError(fmt, ...)\
{\
printf(fmt "\n", ##__VA_ARGS__);\
ASSERT(false);\
} do{} while(0)
#endif

#ifdef NIFLECT_API
#else
    #ifdef WIN32
        #ifdef NIFLECT_EXPORTS
            #define NIFLECT_API __declspec(dllexport)
        #else
            #define NIFLECT_API __declspec(dllimport)
        #endif
    #else
        #ifdef NIFLECT_EXPORTS
		    #define NIFLECT_API __attribute__((visibility("default")))
	    #else
		    #define NIFLECT_API 
	    #endif
    #endif
#endif

#ifdef NIFLECTMODULEREG_API
#else
    #ifdef WIN32
        #ifdef NIFLECTMODULEREG_EXPORTS
            #define NIFLECTMODULEREG_API extern "C" __declspec(dllexport)
        #else
		    #define NIFLECTMODULEREG_API
        #endif
    #else
        #ifdef NIFLECTMODULEREG_EXPORTS
		    #define NIFLECTMODULEREG_API extern "C" __attribute__((visibility("default")))
	    #else
		    #define NIFLECTMODULEREG_API 
	    #endif
    #endif
#endif