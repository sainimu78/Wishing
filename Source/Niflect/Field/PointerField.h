#pragma once
#include "Niflect/Property/FieldProperty.h"

namespace Niflect
{
	//class IPointerTempPointing
	//{
	//public:
	//	virtual AddrType GetPointingBaseAddr() = 0;
	//	virtual void InsertTo(AddrType base) const = 0;
	//};
	//using CSharedPointerTempPointing = TSharedPtr<IPointerTempPointing>;

	class IPointerAccessor
	{
	public:
		virtual AddrType GetPointingBaseAddr(const AddrType& base) const = 0;
		//virtual CSharedPointerTempPointing CreatePointing() const = 0;
	};
	using CSharedPointerAccessor = TSharedPtr<IPointerAccessor>;
	
	class CPointerField : public CField
	{
	public:
		void SetAccessor(const CSharedPointerAccessor& accessor)
		{
			m_accessor = accessor;
		}

	public:
		virtual bool FieldSaveToRwNode(const AddrType& base, CRwNode& rw) const override
		{
			if (auto pointingBase = m_accessor->GetPointingBaseAddr(base))
			{
				this->GetPointingField()->SaveToRwNode(pointingBase, rw);
				return true;
			}
			return false;
		}
		virtual bool FieldLoadFromRwNode(AddrType& base, const CRwNode& rw) const override
		{
			if (auto pointingBase = m_accessor->GetPointingBaseAddr(base))
			{
				this->GetPointingField()->LoadFromRwNode(pointingBase, rw);
				return true;
			}
			return false;
		}

	public:
		virtual bool FieldInitProperty(const Niflect::AddrType& base, Niflect::CProperty* prop, const Niflect::CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, true);

			if (auto pointingBase = m_accessor->GetPointingBaseAddr(base))
			{
				auto pointingProp = this->GetPointingField()->CreatePropertyTree(pointingBase);
				pointingProp->InitParent(prop);
				prop->AddChild(pointingProp);
			}
			return true;
		}

	protected:
		CField* GetPointingField() const
		{
			return this->GetChild(0);
		}

	private:
		CSharedPointerAccessor m_accessor;
	};

	//template <typename T>
	//class TPointerTempPointingAddr : public IPointerTempPointing
	//{
	//public:
	//	virtual AddrType GetPointingBaseAddr() override
	//	{
	//		return &m_elem;
	//	}
	//	virtual void InsertTo(AddrType base) const override
	//	{
	//		auto& instance = *static_cast<T*>(base);
	//		*instance = *m_elem;
	//	}

	//private:
	//	T m_elem;
	//};

	template <typename T>
	class TPointerAccessorAddr : public IPointerAccessor
	{
	public:
		virtual AddrType GetPointingBaseAddr(const AddrType& base) const override
		{
			auto& instance = *static_cast<T*>(base);
			return instance;
		}
		//virtual CSharedPointerTempPointing CreatePointing() const override
		//{
		//	return MakeShared<TPointerTempPointingAddr<T> >();
		//}
	};
	
	template <typename TType>
	struct SFieldCreator<CPointerField, TType>
	{
		static TSharedPtr<CPointerField> Create()
		{
			auto shared1 = Niflect::MakeShared<CPointerField>();
			auto field1 = shared1.Get();
			field1->SetAccessor(MakeShared<TPointerAccessorAddr<TType> >());
			return shared1;
		}
	};
}