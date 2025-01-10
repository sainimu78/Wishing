#pragma once
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