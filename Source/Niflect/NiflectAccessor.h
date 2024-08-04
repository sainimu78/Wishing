#pragma once
#include "Niflect/NiflectBase.h"
#include "Niflect/NiflectAddr.h"
#include "Niflect/Util/TypeUtil.h"
#include "Niflect/Serialization/RwTree.h"

namespace Niflect
{
	using namespace RwTree;

	class CAccessor;
	using CSharedAccessor = TSharedPtr<CAccessor>;

	class CAccessor
	{
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const = 0;
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const = 0;

	public:
		void InitMemberMeta(const CString& name, const AddrOffsetType& offset)
		{
			m_name = name;
			m_addrOffset.SetOffset(offset);
		}
		const CString& GetName() const
		{
			return m_name;
		}

	public:
		void AddChild(const CSharedAccessor& accessor)
		{
			this->InsertChild(accessor, this->GetChildrenCount());
		}
		void InsertChild(const CSharedAccessor& accessor, uint32 idx)
		{
			m_vecChild.insert(m_vecChild.begin() + idx, accessor);
		}
		uint32 GetChildrenCount() const
		{
			return static_cast<uint32>(m_vecChild.size());
		}
		CAccessor* GetChild(uint32 idx) const
		{
			return m_vecChild[idx].Get();
		}
		inline const AddrType GetAddr(const AddrType& base) const
		{
			return static_cast<const char*>(base) + m_addrOffset.GetOffset();
		}
		inline AddrType GetAddr(AddrType& base) const
		{
			return static_cast<char*>(base) + m_addrOffset.GetOffset();
		}

	private:
		CAddrOffset m_addrOffset;
		CString m_name;
		TArrayNif<CSharedAccessor> m_vecChild;
	};
}