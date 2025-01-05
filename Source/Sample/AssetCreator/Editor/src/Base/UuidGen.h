#pragma once
//#include "boost/uuid/uuid.hpp"
//#include <string>

//namespace S3Util
//{
//	//static void CUuidTest()
//	//{
//	//	S3Util::CUuid a;
//	//	if (!a.IsValid())
//	//		printf("\n");
//	//	auto b = S3Util::CUuid::Generate();
//	//	if (b.IsValid())
//	//		printf("\n");
//	//	auto c = b.ToString();
//	//	auto d = S3Util::CUuid(c);
//	//	ASSERT(b == d);
//	//}
//
//	class CUuid
//	{
//	public:
//		CUuid()
//		{
//			std::fill_n(m_id.data, m_id.size(), 0);
//		}
//		CUuid(const std::string& str);
//		std::string ToString() const;
//		size_t GetHash() const
//		{
//			return boost::uuids::hash_value(m_id);
//		}
//		std::string GetHex() const
//		{
//			size_t shortId = this->GetHash();
//			return MyBytesToHexString(&shortId, sizeof(size_t));
//		}
//		bool IsValid() const
//		{
//			return !m_id.is_nil();
//		}
//
//	public:
//		bool operator==(const CUuid& rhs) const
//		{
//			return m_id == rhs.m_id;
//		}
//		bool operator!=(const CUuid& rhs) const
//		{
//			return m_id != rhs.m_id;
//		}
//		bool operator<(const CUuid& rhs) const
//		{
//			return m_id < rhs.m_id;
//		}
//
//	public:
//		static CUuid Generate();
//
//	private:
//		static void MyBytesToHexString(const void* data, size_t bytes, char* str);
//		static std::string MyBytesToHexString(const void* data, size_t numBytes);
//
//	private:
//		boost::uuids::uuid m_id;
//	};
//}

#include "Niflect/NiflectBase.h"

namespace Wishing
{
	class CUuid
	{
	public:
		CUuid();
		CUuid(const Niflect::CString& str);

	public:
		void FromString(const Niflect::CString& str);
		Niflect::CString ToString() const;
		size_t GetHash() const;
		Niflect::CString GetHexString() const;
		bool IsValid() const;

	public:
		static CUuid Generate();

	public:
		bool operator==(const CUuid& rhs) const;
		bool operator!=(const CUuid& rhs) const;
		bool operator<(const CUuid& rhs) const;

	private:
		uint8 m_data[16];
	};

	void _Test_CUuid();
}

//namespace boost
//{
//	namespace uuids
//	{
//		struct uuid;
//	}
//}
//
//namespace Wishing
//{
//	using CSharedUuid = Niflect::TSharedPtr<boost::uuids::uuid>;
//
//	CSharedUuid CreateUuid();
//	Niflect::CString ConvertUuidToString(const CSharedUuid& id);
//	CSharedUuid ConvertStringToUuid(const Niflect::CString& str);
//	size_t GetUuidHash(const CSharedUuid& id);
//	Niflect::CString GetUuidHex(const CSharedUuid& id);
//	bool IsUuidValid(const CSharedUuid& id);
//	bool CompareUuidsEqual(const CSharedUuid& lhs, const CSharedUuid& rhs);
//	bool CompareUuidsLess(const CSharedUuid& lhs, const CSharedUuid& rhs);
//}