#ifdef WIN32
//对于 boost 1.73, 如果链接了 boost 的一些静态库, 如 chrono, 不定义此宏则出现关于 bcrypt 的链接错误, 如不希望定义此宏
//1. 将所有实现移到头文件
//2. cmake 中指定链接
//	if (MSVC)
//		target_link_libraries(${ModuleName} PRIVATE BCrypt)
//	endif()
#define BOOST_UUID_FORCE_AUTO_LINK
#endif

#include "WishingEngine/Base/UuidGen.h"
#include "Niflect/Base/Array.h"
#include "Niflect/Base/StringStream.h"
#include "Niflect/Base/Map.h"
#include "boost/uuid/uuid.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/uuid/random_generator.hpp"
#include "boost/uuid/uuid_io.hpp"

namespace boost
{
	namespace uuids
	{
		//DT?′boost/uuid/uuid_io.hpp:operator>>3??ˉ??±?êó?a′í?ó
		template <typename ch, typename char_traits>
		static std::basic_istream<ch, char_traits>& fromStringStream(std::basic_istream<ch, char_traits>& is, uuid& u)
		{
			const typename std::basic_istream<ch, char_traits>::sentry ok(is);
			if (ok) {
				unsigned char data[16];

				typedef std::ctype<ch> ctype_t;
				ctype_t const& ctype = std::use_facet<ctype_t>(is.getloc());

				ch xdigits[16];
				{
					char szdigits[] = "0123456789ABCDEF";
					ctype.widen(szdigits, szdigits + 16, xdigits);
				}
				ch* const xdigits_end = xdigits + 16;

				ch c;
				for (std::size_t i = 0; i < u.size() && is; ++i) {
					is >> c;
					c = ctype.toupper(c);

					ch* f = std::find(xdigits, xdigits_end, c);
					if (f == xdigits_end) {
						is.setstate(std::ios_base::failbit);
						break;
					}

					unsigned char byte = static_cast<unsigned char>(std::distance(&xdigits[0], f));

					is >> c;
					c = ctype.toupper(c);
					f = std::find(xdigits, xdigits_end, c);
					if (f == xdigits_end) {
						is.setstate(std::ios_base::failbit);
						break;
					}

					byte <<= 4;
					byte |= static_cast<unsigned char>(std::distance(&xdigits[0], f));

					data[i] = byte;

					if (is) {
						if (i == 3 || i == 5 || i == 7 || i == 9) {
							is >> c;
							if (c != is.widen('-')) is.setstate(std::ios_base::failbit);
						}
					}
				}

				if (is) {
					std::copy(data, data + 16, u.data);
				}
			}
			return is;
		}
		static uuid fromString(const std::string& str)
		{
			uuid u;
			std::stringstream ss(str);
			boost::uuids::fromStringStream(ss, u);
			return u;
		}
	}
}

namespace Wishing
{
	static void MyBytesToHexString(const void* data, size_t bytes, char* str)
	{
		static const char kHexToLiteral[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
		for (size_t i = 0; i < bytes; i++)
		{
			uint8_t b = ((uint8_t*)data)[i];
			str[2 * i + 0] = kHexToLiteral[b >> 4];
			str[2 * i + 1] = kHexToLiteral[b & 0xf];
		}
	}
	template <typename TString>
	static void MyBytesToHexString(const void* data, size_t numBytes, TString& result)
	{
		result.resize(numBytes * 2);
		MyBytesToHexString(data, numBytes, &result[0]);
	}
	CUuid::CUuid()
		: m_data{}
	{
	}
	CUuid::CUuid(const Niflect::CString& str)
	{
		this->FromString(str);
	}
	static boost::uuids::uuid& CastRef(CUuid* p)
	{
		return *reinterpret_cast<boost::uuids::uuid*>(p);
	}
	static const boost::uuids::uuid& CastRef(const CUuid* p)
	{
		return *reinterpret_cast<const boost::uuids::uuid*>(p);
	}
	void CUuid::FromString(const Niflect::CString& str)
	{
		Niflect::CStringStream ss(str);
		boost::uuids::fromStringStream(ss, CastRef(this));
	}
	Niflect::CString CUuid::ToString() const
	{
		return boost::lexical_cast<Niflect::CString>(CastRef(this));
	}
	size_t CUuid::GetHash() const
	{
		return boost::uuids::hash_value(CastRef(this));
	}
	Niflect::CString CUuid::GetHexString() const
	{
		size_t shortId = this->GetHash();
		Niflect::CString strHex;
		MyBytesToHexString(&shortId, sizeof(size_t), strHex);
		return strHex;
	}
	bool CUuid::IsValid() const
	{
		return !CastRef(this).is_nil();
	}
	CUuid CUuid::Generate()
	{
		boost::uuids::random_generator gen;
		auto raw = gen();
		CUuid u;
		static_assert(sizeof(CUuid) == sizeof(boost::uuids::uuid), "asdf");
		memcpy(&u, &raw, sizeof(CUuid));
		return u;
	}
	bool CUuid::operator==(const CUuid& rhs) const
	{
		return CastRef(this) == CastRef(&rhs);
	}
	bool CUuid::operator!=(const CUuid& rhs) const
	{
		return CastRef(this) != CastRef(&rhs);
	}
	bool CUuid::operator<(const CUuid& rhs) const
	{
		return CastRef(this) < CastRef(&rhs);
	}
	void _Test_CUuid()
	{
		auto a = CUuid::Generate();
		auto b = a.ToString();
		CUuid c(b);
		ASSERT(a == c);
		printf("UUID: %s\n", b.c_str());

		Niflect::TArray<Wishing::CUuid> array;
		for (uint32 idx = 0; idx < 4096; ++idx)
			array.push_back(Wishing::CUuid::Generate());
		Niflect::TMap<Wishing::CUuid, float> map;
		float val = 0.0f;
		for (auto& it : array)
		{
			val += 1.0f;
			map[it] = val;
		}
		float expected = 0.0f;
		for (auto& it : array)
		{
			expected += 1.0f;
			auto& val = map.at(it);
			ASSERT(val == expected);
		}
	}
}