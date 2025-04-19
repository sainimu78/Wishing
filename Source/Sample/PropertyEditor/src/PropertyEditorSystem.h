#pragma once
#include "Niflect/Base/Map.h"
#include "Property/PropertyNode.h"
#include "Niflect/NiflectTable.h"

using namespace RwTree;

class CPropertyEditorSystem
{
public:
	CPropertyEditorSystem();
	void Init();
	void RegisterBinding(Niflect::CNiflectType* accessorType, Niflect::CNiflectType* propertyType);
	CSharedPropertyNode FindCreateBoundProperty(Niflect::CNiflectType* accessorType) const;

public:
	Niflect::CNiflectTable* GetTable() const { return m_table; }

private:
	Niflect::TMap<Niflect::CNiflectType*, Niflect::CNiflectType*> m_mapAcsToPropType;
	Niflect::CNiflectTable* m_table;
};

CSharedPropertyNode CreateBranchProperty(const CBuildBranchContext& ctx);
void DebugPrintPropertyRecurs(CPropertyNode* propParent, uint32 depth);