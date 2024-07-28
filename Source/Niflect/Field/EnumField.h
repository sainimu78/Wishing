#pragma once
#include "Niflect/Property/FieldProperty.h"
#include "Niflect/Type/NiflectType.h"

namespace Niflect
{
	class IUintXEnumAccessor
	{
	public:
		virtual uint32 GetUInt(const AddrType& base) const = 0;
		virtual void SetUInt(AddrType& base, uint32 idx) const = 0;
	};
	using CSharedUintXEnumAccessor = TSharedPtr<IUintXEnumAccessor>;

	class CEnumField : public CField
	{
		typedef CField inherited;
	public:
		void SetAccessor(const CSharedUintXEnumAccessor& accessor)
		{
			m_accessor = accessor;
		}

	public:
		virtual bool FieldSaveToRwNode(const AddrType& base, CRwNode& rw) const override
		{
			auto e = this->GetEnum();
			auto& rwValue = rw->ToValue();
			auto& name = e->GetName(m_accessor->GetUInt(base));
			ValueReadWrite::Save(rwValue, name);
			return true;
		}
		virtual bool FieldLoadFromRwNode(AddrType& base, const CRwNode& rw) const override
		{
			CString name;
			auto e = this->GetEnum();
			auto& rwValue = rw->ToValue();
			ValueReadWrite::Load(rwValue, name);
			auto idx = e->FindIndex(name);
			ASSERT(idx != INDEX_NONE);
			m_accessor->SetUInt(base, idx);
			return true;
		}

	public:
		virtual bool FieldInitProperty(const Niflect::AddrType& base, Niflect::CProperty* prop, const Niflect::CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, true);
			return true;
		}

	private:
		CEnum* GetEnum() const
		{
			return Cast<CEnum>(inherited::GetType());
		}

	private:
		CSharedUintXEnumAccessor m_accessor;
	};

	template <typename TUintXType>
	class TUintXEnumAccessorAddr : public IUintXEnumAccessor
	{
	public:
		virtual uint32 GetUInt(const AddrType& base) const override
		{
			return *static_cast<TUintXType*>(base);
		}
		virtual void SetUInt(AddrType& base, uint32 idx) const override
		{
			*static_cast<TUintXType*>(base) = idx;
		}
	};
	
	template <typename TEnum>
	static TSharedPtr<CEnumField> CreateEnumField()
	{
		auto shared1 = Niflect::MakeShared<CEnumField>();
		auto field1 = shared1.Get();
		field1->SetAccessor(MakeShared<TUintXEnumAccessorAddr<typename std::underlying_type<TEnum>::type> >());
		return shared1;
	}

	template <typename TType>
	struct SFieldCreator<CEnumField, TType>
	{
		static TSharedPtr<CEnumField> Create()
		{
			return CreateEnumField<TType>();
		}
	};
}