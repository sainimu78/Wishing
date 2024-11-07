#include "NiflectGen/Generator/BypassSTLHeaders.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Util/SystemUtil.h"

namespace NiflectGen
{
	using WriteHeaderFileFunc = std::function<void(Niflect::CString& code)>;

	static void Write_map(Niflect::CString& code)
	{
		code =
R"(#pragma once
#include <xmemory>
#include <type_traits>

namespace std
{
template<class _Kty,
	class _Ty,
	class _Pr = less<_Kty>,
	class _Alloc = allocator<pair<const _Kty, _Ty> > >
	class map
	{
	};
})";
	}
	static void Write_set(Niflect::CString& code)
	{
		code =
R"(#pragma once
#include <xmemory>
#include <type_traits>

namespace std
{
template<class _Kty,
	class _Pr = less<_Kty>,
	class _Alloc = allocator<_Kty> >
	class set
	{
	};
})";
	}
	static void Write_sstream(Niflect::CString& code)
	{
		code =
R"(#pragma once
#include <xmemory>
#include <string>

namespace std
{
	template <class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
	class basic_stringstream
	{

	};
})";
	}
	static void Write_string(Niflect::CString& code)
	{
		code =
R"(#pragma once
#include <xmemory>

namespace std
{
template<class _Elem,
	class _Traits,
	class _Alloc>
	class basic_string
	{
	};

template<class _Elem>
	struct char_traits
	{
	};

template<> struct char_traits<char>
	{	// properties of a string or stream char element
	};

typedef basic_string<char, char_traits<char>, allocator<char> >
	string;
})";
	}
	static void Write_type_traits(Niflect::CString& code)
	{
		code =
R"(#pragma once

namespace std
{
template<class _Ty = void>
	struct less
	{
	};
	
template<class _Kty>
	struct hash
	{
	};

template <class _From, class _To>
	struct is_convertible
	{
		// determine whether _From is convertible to _To
	};	
})";
	}
	static void Write_unordered_map(Niflect::CString& code)
	{
		code =
R"(#pragma once
#include <xmemory>
#include <type_traits>
#include <utility>

namespace std
{
template<class _Kty,
	class _Ty,
	class _Hasher = hash<_Kty>,
	class _Keyeq = equal_to<_Kty>,
	class _Alloc = allocator<pair<const _Kty, _Ty> > >
	class unordered_map
	{
	};
})";
	}
	static void Write_unordered_set(Niflect::CString& code)
	{
		code =
R"(#pragma once
#include <xmemory>
#include <type_traits>
#include <utility>

namespace std
{
template <class _Kty, class _Hasher = hash<_Kty>, class _Keyeq = equal_to<_Kty>,
    class _Alloc = allocator<_Kty>>
	class unordered_set
	{
	};
})";
	}
	static void Write_vector(Niflect::CString& code)
	{
		code =
R"(#pragma once
#include <xmemory>

namespace std
{
template<class _Ty,
	class _Alloc = allocator<_Ty> >
	class vector
	{
	};
})";
	}
	static void Write_utility(Niflect::CString& code)
	{
		code =
R"(#pragma once

namespace std
{
template<class _Ty1,
	class _Ty2>
	struct pair
	{
	_Ty1 first;		// the first stored value
	_Ty2 second;	// the second stored value
	};
	
template<class _Ty = void>
	struct equal_to
	{
	};
})";
	}
	static void Write_xmemory(Niflect::CString& code)
	{
		code =
R"(#pragma once

namespace std
{
template<class _Ty>
	class allocator
	{
	};
})";
	}
	struct SHeaderData
	{
		const char* m_headerFileName;
		const bool m_withBypassDefinition;
	};
	void GenerateBypassSTLHeaders(const Niflect::CString& headersDirPath)
	{
		SHeaderData arrAllNeeded[] = {
			{"algorithm", false},
			{"array", false},
			{"cassert", false},
			{"deque", false},
			{"exception", false},
			{"fstream", false},
			{"functional", false},
			{"hash", false},
			{"hash_map", false},
			{"hash_set", false},
			{"ios", false},
			{"iosfwd", false},
			{"iostream", false},
			{"istream", false},
			{"iterator", false},
			{"list", false},
			{"locale", false},
			{"map", true},//Write_map
			{"new", false},
			{"numeric", false},
			{"ostream", false},
			{"queue", false},
			{"regex", false},
			{"set", true},//Write_set
			{"sstream", true},//Write_sstream
			{"stack", false},
			{"streambuf", false},
			{"string", true},//Write_string
			{"system_error", false},
			{"tuple", false},
			{"typeindex", false},
			{"typeinfo", false},
			{"type_traits", true},//Write_type_traits
			{"unordered_map", true},//Write_unordered_map
			{"unordered_set", true},//Write_unordered_set
			{"utility", true},//Write_utility
			{"vector", true},//Write_vector
			{"xfunctional", false},
			{"xhash", false},
			{"xiosbase", false},
			{"xlocale", false},
			{"xlocbuf", false},
			{"xmemory", true},//Write_xmemory
			{"xstring", false},
			{"xtree", false},
			{"xutility", false},
			{"xxatomic", false},
		};

		Niflect::TArrayNif<WriteHeaderFileFunc> vecWriteFunc;
		vecWriteFunc.push_back(&Write_map);
		vecWriteFunc.push_back(&Write_set);
		vecWriteFunc.push_back(&Write_sstream);
		vecWriteFunc.push_back(&Write_string);
		vecWriteFunc.push_back(&Write_type_traits);
		vecWriteFunc.push_back(&Write_unordered_map);
		vecWriteFunc.push_back(&Write_unordered_set);
		vecWriteFunc.push_back(&Write_utility);
		vecWriteFunc.push_back(&Write_vector);
		vecWriteFunc.push_back(&Write_xmemory);

		Niflect::CString defaultBypassHeaderCode;

		Niflect::TArrayNif<CMemSource> vecMemSrc;
		CMemSource memSrcDefaultHeader;
		{
			memSrcDefaultHeader.m_filePath = NiflectUtil::ConcatPath(headersDirPath, NiflectGenDefinition::NiflectFramework::BypassSTL::DefaultHeaderFileName);

			CSimpleCppWriter writer(defaultBypassHeaderCode);
			writer.AddHeaderFirstLine();
			writer.AddInclude(memSrcDefaultHeader.m_filePath);
		}

		uint32 cnt = sizeof(arrAllNeeded) / sizeof(SHeaderData);
		vecMemSrc.resize(cnt);
		uint32 idxFunc = 0;
		Niflect::TArrayNif<uint32> vecIdxWrittenByFunc;
		for (uint32 idx = 0; idx < cnt; ++idx)
		{
			auto& item = arrAllNeeded[idx];
			auto& memSrc = vecMemSrc[idx];
			memSrc.m_filePath = NiflectUtil::ConcatPath(headersDirPath, item.m_headerFileName);
			if (!item.m_withBypassDefinition)
			{
				memSrc.m_data = defaultBypassHeaderCode;
			}
			else
			{
				vecIdxWrittenByFunc.push_back(idx);
				vecWriteFunc[idxFunc++](memSrc.m_data);
			}
		}
		{
			CSimpleCppWriter writer(memSrcDefaultHeader.m_data);
			writer.AddHeaderFirstLine();
			for (auto& it : vecIdxWrittenByFunc)
				writer.AddSystemInclude(arrAllNeeded[it].m_headerFileName);
			vecMemSrc.push_back(memSrcDefaultHeader);
		}

		ASSERT(vecWriteFunc.size() == idxFunc);

		{
			//已尝试不生成文件, 使用 CXUnsavedFile 传入 clang_parseTranslationUnit, 发现这样无法在解析时找到内存中的文件, 因此仍须生成到磁盘, 至少可避免要求用户指定 Bypass 的路径
			for (auto& it : vecMemSrc)
			{
				NiflectUtil::MakeDirectories(it.m_filePath);
				NiflectUtil::WriteStringToFile(it.m_data, it.m_filePath);
			}
		}
	}
}