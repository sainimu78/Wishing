#pragma once
#include "Niflect/NiflectBase.h"
#include "Niflect/NiflectAddr.h"
#include "Niflect/Util/TypeUtil.h"
#include "Niflect/Serialization/RwTree.h"

namespace Niflect
{
	using namespace RwTree;

	class CNiflectType;

	//template <typename T>
	//static CNiflectType* StaticGetType();

	class CField;

	using CSharedField = TSharedPtr<CField>;

	class CField
	{
	public:
		CField()
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
		//void InitOffset(const AddrOffsetType& offset)
		//{
		//	m_addrOffset.SetOffset(offset);
		//}
		CNiflectType* GetType() const
		{
			return m_type;
		}
		const CString& GetName() const
		{
			return m_name;
		}

	public:
		void AddChild(const CSharedField& field)
		{
			this->InsertChild(field, this->GetChildrenCount());
		}
		void InsertChild(const CSharedField& field, uint32 idx)
		{
			m_vecChild.insert(m_vecChild.begin() + idx, field);
		}
		uint32 GetChildrenCount() const
		{
			return static_cast<uint32>(m_vecChild.size());
		}
		CField* GetChild(uint32 idx) const
		{
			return m_vecChild[idx].Get();
		}

	private:
		CString m_name;
		CNiflectType* m_type;
		TArrayNif<CSharedField> m_vecChild;
		CAddrOffset m_addrOffset;
	};

	//template <typename TField, typename TType>
	//struct SFieldCreator
	//{
	//	static TSharedPtr<TField> Create()
	//	{
	//		return MakeShared<TField>();
	//	}
	//};

	//template <typename TField, typename TType>
	//static TSharedPtr<TField> CreateField()
	//{
	//	auto shared = SFieldCreator<TField, TType>::Create();
	//	auto field = shared.Get();
	//	field->InitType(StaticGetType<TType>());
	//	return shared;
	//}
}