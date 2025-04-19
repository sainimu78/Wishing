#pragma once
#include "Niflect/NiflectType.h"

using namespace RwTree;

class CPropertyEditorSystem;

class CPropertyBranchContext
{
public:
	CPropertyBranchContext(CPropertyEditorSystem* sys, Niflect::CNiflectType* type, CRwNode* rw)
		: m_sys(sys)
		, m_type(type)
		, m_rw(rw)
	{
	}
	CPropertyEditorSystem* m_sys;
	CRwNode* m_rw;
	Niflect::CNiflectType* m_type;
};