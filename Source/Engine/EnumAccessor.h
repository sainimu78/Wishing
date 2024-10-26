#pragma once
#include "Niflect/NiflectAccessor.h"
#include "Niflect/NiflectType.h"

namespace Engine
{
	using namespace RwTree;

	class CEnumClassAccessor : public Niflect::CAccessor
	{
		typedef Niflect::CAccessor inherited;
	public:
		virtual bool SaveToRwNode2222(const AddrType offsetBase, CRwNode* rw) const override
		{
			//typename std::underlying_type<TEnum>::type >, 可获取枚举对应的整数类型

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
			case 1: *static_cast<uint8*>(offsetBase) = idx; break;
			case 2: *static_cast<uint16*>(offsetBase) = idx; break;
			case 4: *static_cast<uint32*>(offsetBase) = idx; break;
			default:
				ASSERT(false);
				break;
			}
			return true;
		}

	private:
		Niflect::CEnum* GetEnum() const
		{
			return Niflect::CEnum::Cast(inherited::GetType());
		}
	};

	class CEnumBitMaskAccessor : public Niflect::CAccessor
	{
		typedef Niflect::CAccessor inherited;
	public:
		virtual bool SaveToRwNode2222(const AddrType offsetBase, CRwNode* rw) const override
		{
			//typename std::underlying_type<TEnum>::type >, 可获取枚举对应的整数类型
			return true;
		}
		virtual bool LoadFromRwNode2222(AddrType offsetBase, const CRwNode* rw) const override
		{
			return true;
		}

	private:
		Niflect::CEnum* GetEnum() const
		{
			return Niflect::CEnum::Cast(inherited::GetType());
		}
	};
}