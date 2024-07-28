#pragma once
#include "Niflect/Property/FieldProperty.h"

namespace Niflect
{
	//class CCompoundField : public CField
	//{
	//public:
	//	virtual bool SaveToRwNode(const AddrType& ownerBase, CRwNode& rw) const override
	//	{
	//		auto count = this->GetChildrenCount();
	//		for (uint32 idx = 0; idx < count; ++idx)
	//		{
	//			auto child = this->GetChild(idx);
	//			ASSERT(!child->GetName().empty());

	//			//uint32 childIndex;
	//			//auto rwChild = AddRwNode(rw, child->GetName(), &childIndex);
	//			//child->SaveToRwNode(objBase, rwChild);

	//			auto rwChild = rw->CreateNode();
	//			auto childAccessor = child->GetAccessor();
	//			if (childAccessor->SaveToRwNode(ownerBase, rwChild))
	//				AddExistingRwNode(rw, child->GetName(), rwChild);
	//		}
	//		return true;
	//	}
	//	virtual bool LoadFromRwNode(AddrType& ownerBase, const CRwNode& rw) const override
	//	{
	//		auto count = this->GetChildrenCount();
	//		for (uint32 idx = 0; idx < count; ++idx)
	//		{
	//			auto child = this->GetChild(idx);
	//			ASSERT(!child->GetName().empty());
	//			auto rwChild = FindRwNode(rw, child->GetName());
	//			auto childAccessor = child->GetAccessor();
	//			childAccessor->LoadFromRwNode(ownerBase, rwChild);
	//		}
	//		return true;
	//	}

	////public:
	////	virtual CSharedProperty CreatePropertyTree(const AddrType& base) override
	////	{
	////		auto parentProp = Niflect::MakeShared<Niflect::CFieldProperty>();
	////		parentProp->InitMeta(this->GetName(), base, false);
	////		parentProp->SetField(this);
	////		for (uint32 idx = 0; idx < this->GetChildrenCount(); ++idx)
	////		{
	////			auto childField = this->GetChild(idx);
	////			auto childBase = childField->GetBaseAddr(base);
	////			auto childProp = childField->CreatePropertyTree(childBase);
	////			parentProp->AddChild(childProp);
	////		}
	////		return parentProp;
	////	}
	//};

	class CCompoundField : public CField
	{
	public:
		virtual bool FieldSaveToRwNode(const AddrType& base, CRwNode& rw) const override
		{
			auto count = this->GetChildrenCount();
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto child = this->GetChild(idx);
				ASSERT(!child->GetName().empty());

				//uint32 childIndex;
				//auto rwChild = AddRwNode(rw, child->GetName(), &childIndex);
				//child->SaveToRwNode(objBase, rwChild);

				auto rwChild = rw->CreateNode();
				if (child->SaveToRwNode(base, rwChild))
					AddExistingRwNode(rw, child->GetName(), rwChild);
			}
			return true;
		}
		virtual bool FieldLoadFromRwNode(AddrType& base, const CRwNode& rw) const override
		{
			auto count = this->GetChildrenCount();
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto child = this->GetChild(idx);
				ASSERT(!child->GetName().empty());
				auto rwChild = FindRwNode(rw, child->GetName());
				child->LoadFromRwNode(base, rwChild);
			}
			return true;
		}
		virtual bool FieldInitProperty(const AddrType& base, CProperty* prop, const CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, false);

			for (uint32 idx = 0; idx < this->GetChildrenCount(); ++idx)
			{
				auto childField = this->GetChild(idx);
				auto childProp = childField->CreatePropertyTree(base, context);
				childProp->InitParent(prop);
				prop->AddChild(childProp);
			}
			return true;
		}
	};
}