#pragma once
#include "Niflect/NiflectAccessor.h"
#include "Niflect/NiflectType.h"

namespace Engine
{
	using namespace RwTree;

	//class IUintXEnumAccessor
	//{
	//public:
	//	virtual uint32 GetUInt(const AddrType& base) const = 0;
	//	virtual void SetUInt(AddrType& base, uint32 idx) const = 0;
	//};
	//using CSharedUintXEnumAccessor = TSharedPtr<IUintXEnumAccessor>;

	class CUnitXEnumAccessor : public Niflect::CAccessor
	{
		typedef Niflect::CAccessor inherited;
	public:
		virtual bool SaveToRwNode2222(const AddrType offsetBase, CRwNode* rw) const override
		{
			auto et = this->GetEnum();
			auto rwValue = rw->ToValue();
			uint32 idx = INDEX_NONE;
			switch (et->GetTypeSize())
			{
			case 1: idx = *static_cast<const uint8*>(offsetBase); break;
			case 2: idx = *static_cast<const uint16*>(offsetBase); break;
			case 4: idx = *static_cast<const uint32*>(offsetBase); break;
			default:
				ASSERT(false);
				break;
			}
			auto& name = et->GetEnumConstNameByIndex(idx);
			rwValue->SetString(name);
			return true;
		}
		virtual bool LoadFromRwNode2222(AddrType offsetBase, const CRwNode* rw) const override
		{
			auto et = this->GetEnum();
			auto rwValue = rw->GetValue();
			auto name = rwValue->GetString();
			auto idx = et->FindIndexByEnumConstName(name);
			ASSERT(idx != INDEX_NONE);//可能由于此枚举类型的版本不同导致查找失败
			switch (et->GetTypeSize())
			{
			case 1: idx = *static_cast<uint8*>(offsetBase) = idx; break;
			case 2: idx = *static_cast<uint16*>(offsetBase) = idx; break;
			case 4: idx = *static_cast<uint32*>(offsetBase) = idx; break;
			default:
				ASSERT(false);
				break;
			}
			return true;
		}

	public:
		Niflect::CEnum* GetEnum() const
		{
			return Niflect::CEnum::Cast(inherited::GetType());
		}
	};

	//template <typename TUintXType>
	//class TUintXEnumAccessorAddr : public IUintXEnumAccessor
	//{
	//public:
	//	virtual uint32 GetUInt(const AddrType& base) const override
	//	{
	//		return *static_cast<TUintXType*>(base);
	//	}
	//	virtual void SetUInt(AddrType& base, uint32 idx) const override
	//	{
	//		*static_cast<TUintXType*>(base) = idx;
	//	}
	//};

	//template <typename TEnum>
	//static TSharedPtr<CEnumField> CreateEnumField()
	//{
	//	auto shared1 = Niflect::MakeShared<CEnumField>();
	//	auto field1 = shared1.Get();
	//	field1->SetAccessor(MakeShared<TUintXEnumAccessorAddr<typename std::underlying_type<TEnum>::type> >());
	//	return shared1;
	//}

	//template <typename TType>
	//struct SFieldCreator<CEnumField, TType>
	//{
	//	static TSharedPtr<CEnumField> Create()
	//	{
	//		return CreateEnumField<TType>();
	//	}
	//};
}