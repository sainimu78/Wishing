#include "Property/PropertyNode.h"
#include "PropertyEditorSystem.h"

void CPropertyGroup::BuildNode(const CBuildBranchContext& ctx)
{
	auto& layout = ctx.m_type->GetTypeLayout();
	if (layout.m_vecSection.size() == 1)
	{
		auto& sect = layout.m_vecSection[0];
		this->BuildFields(ctx, sect);
	}
	else
	{
		ASSERT(false);
		for (auto& it : layout.m_vecSection)
		{

		}
	}
}
void CPropertyGroup::BuildFields(const CBuildBranchContext& ctx, Niflect::CNiflectType* type)
{
	auto& vecFields = type->GetFields();
	for (uint32 idx = 0; idx < vecFields.size(); ++idx)
	{
		auto rwField = ctx.m_rw->GetNode(idx);
		auto& field = vecFields[idx];
		auto propField = CreateBranchProperty(CBuildBranchContext(ctx.m_sys, field.GetType(), rwField));
		propField->InitName(field.GetName());
		this->AddNode(propField);
	}
}

void CFloatProperty::BuildNode(const CBuildBranchContext& ctx)
{
	ASSERT(ctx.m_rw->IsValue());
	auto& value = ctx.m_rw->GetValue()->GetFloat();
	m_rw = CreateRwNode();
	SetRwValueAs<float>(m_rw->ToValue(), value);
}