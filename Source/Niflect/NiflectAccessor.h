#pragma once
#include "Niflect/NiflectBase.h"
#include "Niflect/NiflectAddr.h"
#include "Niflect/Util/TypeUtil.h"
#include "Niflect/Serialization/RwTree.h"

namespace Niflect
{
	using namespace RwTree;

	class CNiflectType;

	class CAccessor;
	using CSharedAccessor = TSharedPtr<CAccessor>;

	class CAccessor
	{
	public:
		CAccessor()
			: m_type(NULL)
		{

		}

	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const = 0;
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const = 0;

	public:
		void InitType(CNiflectType* type)
		{
			m_type = type;
		}
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
		void InitElementAccessor(const CSharedAccessor& accessor)
		{
			m_elemAccessor = accessor;
		}
		CAccessor* GetElementAccessor() const
		{
			return m_elemAccessor.Get();
		}

	protected:
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
		CSharedAccessor m_elemAccessor;
		CNiflectType* m_type;
	};

	class CCompoundAccessor : public CAccessor
	{
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto count = this->GetChildrenCount();
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto childAccessor = this->GetChild(idx);
				ASSERT(!childAccessor->GetName().empty());
				auto rwChild = CreateRwNode();
				if (childAccessor->SaveToRwNode(offsetBase, rwChild.Get()))
					AddExistingRwNode(rw, childAccessor->GetName(), rwChild);
			}
			return true;
		}
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto count = this->GetChildrenCount();
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto childAccessor = this->GetChild(idx);
				ASSERT(!childAccessor->GetName().empty());
				auto rwChild = FindRwNode(rw, childAccessor->GetName());
				childAccessor->LoadFromRwNode(offsetBase, rwChild);
			}
			return true;
		}
	};
}