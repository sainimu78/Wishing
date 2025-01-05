#include "Base/Uuid.h"
#include "boost/uuid/uuid.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
//#include <iostream>

namespace boost
{
	namespace uuids
	{
		//修复boost/uuid/uuid_io.hpp:operator>>出警告被视为错误
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
//
//namespace S3Util
//{
//	CUuid::CUuid(const std::string& str)
//	{
//		m_id = boost::uuids::fromString(str);
//	}
//	std::string CUuid::ToString() const
//	{
//		return boost::lexical_cast<std::string>(m_id);
//	}
//	CUuid CUuid::Generate()
//	{
//		CUuid u;
//		boost::uuids::random_generator gen;
//		u.m_id = gen();
//		return u;
//	}
//	void CUuid::MyBytesToHexString(const void* data, size_t bytes, char* str)
//	{
//		static const char kHexToLiteral[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
//		for (size_t i = 0; i < bytes; i++)
//		{
//			uint8_t b = ((uint8_t*)data)[i];
//			str[2 * i + 0] = kHexToLiteral[b >> 4];
//			str[2 * i + 1] = kHexToLiteral[b & 0xf];
//		}
//	}
//	std::string CUuid::MyBytesToHexString(const void* data, size_t numBytes)
//	{
//		std::string result;
//		result.resize(numBytes * 2);
//		MyBytesToHexString(data, numBytes, &result[0]);
//		return result;
//	}
//}

namespace Wishing
{
	CSharedUuid CreateUuid()
	{
		boost::uuids::random_generator gen;
		return Niflect::MakeShared<boost::uuids::uuid>(gen());
	}
	Niflect::CString ConvertUuidToString(const CSharedUuid& id)
	{
		if(id != NULL)
			return boost::lexical_cast<Niflect::CString>(*id);
		return Niflect::CString();
	}
	CSharedUuid ConvertStringToUuid(const Niflect::CString& str)
	{
		auto u = Niflect::MakeShared<boost::uuids::uuid>();
		Niflect::CStringStream ss(str);
		boost::uuids::fromStringStream(ss, *u);
		return u;
	}
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
	size_t GetUuidHash(const CSharedUuid& id)
	{
		return boost::uuids::hash_value(*id);
	}
	Niflect::CString GetUuidHex(const CSharedUuid& id)
	{
		size_t shortId = GetUuidHash(id);
		Niflect::CString strHex;
		MyBytesToHexString(&shortId, sizeof(size_t), strHex);
		return strHex;
	}
	bool IsUuidValid(const CSharedUuid& id)
	{
		if (id != NULL)
			return !id->is_nil();
		return false;
	}
	bool CompareUuidsEqual(const CSharedUuid& lhs, const CSharedUuid& rhs)
	{
		if (!lhs && !rhs)
			return true;
		if (!lhs || !rhs)
			return false;
		return *lhs == *rhs;
	}
	bool CompareUuidsLess(const CSharedUuid& lhs, const CSharedUuid& rhs)
	{
		if (lhs == NULL && rhs == NULL)
			return false;
		else if (lhs == NULL)
			return true;
		else if (rhs == NULL)
			return false;
		return *lhs < *rhs;
	}
}