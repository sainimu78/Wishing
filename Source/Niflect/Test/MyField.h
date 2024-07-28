#pragma once
#include "Niflect/Property/FieldProperty.h"
//#include "Niflect/Test/NiflectGenerated/MyModule/MyField.gen.h"
//#include "Niflect/Field/NiflectField.h"

namespace MyTestClassScope
{
	using namespace TreeReadWrite2;
	
	//class CFloatField : public Niflect::CField
	//{
	//public:
	//	virtual bool SaveToRwNode(const Niflect::AddrType& ownerBase, CRwNode& rw) const override
	//	{
	//		auto& instance = *static_cast<float*>(ownerBase);
	//		auto& rwValue = rw->ToValue();
	//		return ValueReadWrite::Save(rwValue, instance);
	//	}
	//	virtual bool LoadFromRwNode(Niflect::AddrType& ownerBase, const CRwNode& rw) const override
	//	{
	//		auto& instance = *static_cast<float*>(ownerBase);
	//		auto& rwValue = rw->ToValue();
	//		return ValueReadWrite::Load(rwValue, instance);
	//	}

	////public:
	////	virtual Niflect::CSharedProperty CreatePropertyTree(const Niflect::AddrType& base) override
	////	{
	////		auto parentProp = Niflect::MakeShared<Niflect::CFieldProperty>();
	////		parentProp->InitMeta(this->GetName(), base, true);
	////		parentProp->SetField(this);
	////		return parentProp;
	////	}
	//};
	//class CStringField : public Niflect::CField
	//{
	//public:
	//	virtual bool SaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
	//	{
	//		auto& instance = *static_cast<Niflect::CString*>(base);
	//		auto& rwValue = rw->ToValue();
	//		return ValueReadWrite::Save(rwValue, instance);
	//	}
	//	virtual bool LoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
	//	{
	//		auto& instance = *static_cast<Niflect::CString*>(base);
	//		auto& rwValue = rw->ToValue();
	//		return ValueReadWrite::Load(rwValue, instance);
	//	}

	//public:
	//	virtual Niflect::CSharedProperty CreatePropertyTree(const Niflect::AddrType& base) override
	//	{
	//		auto parentProp = Niflect::MakeShared<Niflect::CFieldProperty>();
	//		parentProp->InitMeta(this->GetName(), base, true);
	//		parentProp->SetField(this);
	//		return parentProp;
	//	}
	//};
	//class CBoolField : public Niflect::CField
	//{
	//public:
	//	virtual bool SaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
	//	{
	//		auto& instance = *static_cast<bool*>(base);
	//		auto& rwValue = rw->ToValue();
	//		return ValueReadWrite::Save(rwValue, instance);
	//	}
	//	virtual bool LoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
	//	{
	//		auto& instance = *static_cast<bool*>(base);
	//		auto& rwValue = rw->ToValue();
	//		return ValueReadWrite::Load(rwValue, instance);
	//	}

	//public:
	//	virtual Niflect::CSharedProperty CreatePropertyTree(const Niflect::AddrType& base) override
	//	{
	//		auto parentProp = Niflect::MakeShared<Niflect::CFieldProperty>();
	//		parentProp->InitMeta(this->GetName(), base, true);
	//		parentProp->SetField(this);
	//		return parentProp;
	//	}
	//};
	
	class CFloatField : public Niflect::CField
	{
	protected:
		virtual bool FieldSaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
		{
			auto& instance = *static_cast<float*>(base);
			auto& rwValue = rw->ToValue();
			return ValueReadWrite::Save(rwValue, instance);
		}
		virtual bool FieldLoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
		{
			auto& instance = *static_cast<float*>(base);
			auto& rwValue = rw->ToValue();
			return ValueReadWrite::Load(rwValue, instance);
		}
		virtual bool FieldInitProperty(const Niflect::AddrType& base, Niflect::CProperty* prop, const Niflect::CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, true);
			return true;
		}
	};
	class CStringField : public Niflect::CField
	{
	public:
		virtual bool FieldSaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
		{
			auto& instance = *static_cast<Niflect::CString*>(base);
			auto& rwValue = rw->ToValue();
			return ValueReadWrite::Save(rwValue, instance);
		}
		virtual bool FieldLoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
		{
			auto& instance = *static_cast<Niflect::CString*>(base);
			auto& rwValue = rw->ToValue();
			return ValueReadWrite::Load(rwValue, instance);
		}
		virtual bool FieldInitProperty(const Niflect::AddrType& base, Niflect::CProperty* prop, const Niflect::CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, true);
			return true;
		}
	};
	using CStringField2 =  CStringField;
	//class CStringField2 : public Niflect::CField
	//{
	//public:
	//	virtual bool FieldSaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
	//	{
	//		auto& instance = *static_cast<Niflect::CString*>(base);
	//		auto& rwValue = rw->ToValue();
	//		return ValueReadWrite::Save(rwValue, instance);
	//	}
	//	virtual bool FieldLoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
	//	{
	//		auto& instance = *static_cast<Niflect::CString*>(base);
	//		auto& rwValue = rw->ToValue();
	//		return ValueReadWrite::Load(rwValue, instance);
	//	}
	//	virtual bool FieldInitProperty(const Niflect::AddrType& base, Niflect::CProperty* prop, const Niflect::CCreatingPropertyTreeContext& context) const override
	//	{
	//		prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, true);
	//		return true;
	//	}
	//};
	class CBoolField : public Niflect::CField
	{
	public:
		virtual bool FieldSaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
		{
			auto& instance = *static_cast<bool*>(base);
			auto& rwValue = rw->ToValue();
			return ValueReadWrite::Save(rwValue, instance);
		}
		virtual bool FieldLoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
		{
			auto& instance = *static_cast<bool*>(base);
			auto& rwValue = rw->ToValue();
			return ValueReadWrite::Load(rwValue, instance);
		}
		virtual bool FieldInitProperty(const Niflect::AddrType& base, Niflect::CProperty* prop, const Niflect::CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, true);
			return true;
		}
	};
}