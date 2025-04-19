#include "PropertyEditorSystem.h"
#include "PropertyEditor_private.h"
#include "Niflect/Util/DebugUtil.h"

CPropertyEditorSystem::CPropertyEditorSystem()
	: m_table(NULL)
{

}
void CPropertyEditorSystem::Init()
{
	auto reg = Niflect::GetModuleRegistry();
	reg->InitRegisteredModules();

	ASSERT(reg->GetModulesCount() == 1);
	auto mod = reg->GetModuleByIndex(0);
	m_table = mod->GetTable();
}
void CPropertyEditorSystem::RegisterBinding(Niflect::CNiflectType* accessorType, Niflect::CNiflectType* propertyType)
{
	auto ret = m_mapAcsToPropType.insert({ accessorType, propertyType });
	ASSERT(ret.second);
}
CSharedPropertyNode CPropertyEditorSystem::FindCreateBoundProperty(Niflect::CNiflectType* accessorType) const
{
	auto itFound = m_mapAcsToPropType.find(accessorType);
	if (itFound != m_mapAcsToPropType.end())
	{
		auto& propType = itFound->second;
		return Niflect::NiflectTypeMakeShared<CPropertyNode>(propType);
	}
	return NULL;
}

CSharedPropertyNode CreateBranchProperty(const CBuildBranchContext& ctx)
{
	auto prop = ctx.m_sys->FindCreateBoundProperty(GetAccessorType(ctx.m_type));
	if (prop == NULL)
	{
		ASSERT(false);
	}
	prop->InitAccessorType(ctx.m_type);
	prop->BuildNode(ctx);
	return prop;
}
void DebugPrintPropertyRecurs(CPropertyNode* propParent, uint32 depth)
{
	auto strDepth = NiflectUtil::DebugIndentToString(depth);
	auto propName = propParent->m_name;
	if (propName.empty())
		propName = "Not a field";
	Niflect::CString propValue;
	if (auto rw = propParent->GetRwData())
	{
		if (rw->IsValue())
		{
			switch (rw->GetValue()->GetType())
			{
			case ERwValueType::Float:
			{
				Niflect::CStringStream ss;
				ss << rw->GetValue()->GetFloat();
				propValue = ss.str();
				break;
			}
			default:
				ASSERT(false);
				break;
			}
		}
	}
	if (propValue.empty())
		propValue = "Not an item";
	printf("%s%s, %s, %s\n", strDepth.c_str(), propParent->m_accessorType->GetTypeName().c_str(), propName.c_str(), propValue.c_str());

	depth++;
	for (auto& it : propParent->m_vecNode)
		DebugPrintPropertyRecurs(it.Get(), depth);
}