#pragma once
#include "Niflect/NiflectCommon.h"

namespace Niflect
{
	using AddrType = void*;
	using AddrOffsetType = ptrdiff_t;
	using ArrayIndex = uint32;
	
	class CAddrOffset
	{
	public:
		enum __InternalConst : AddrOffsetType { None };

	public:
		CAddrOffset()
			: m_offsetInBytes(None)
		{
		}
		CAddrOffset(const AddrOffsetType& offsetInBytes)
			: m_offsetInBytes(offsetInBytes)
		{
		}
		void SetOffset(const AddrOffsetType& offsetInBytes)
		{
			m_offsetInBytes = offsetInBytes;
		}
		const AddrOffsetType& GetOffset() const
		{
			return m_offsetInBytes;
		}

	public:
		inline AddrType GetAddr(const AddrType& base) const
		{
			return static_cast<char*>(base) + m_offsetInBytes;
		}

	private:
		AddrOffsetType m_offsetInBytes;
	};

	template <typename U, typename T>
	inline static AddrOffsetType GetMemberVariableOffset(U T::*member)
	{
		return (char*)&((T*)nullptr->*member) - (char*)nullptr;
	}
}