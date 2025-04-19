#pragma once
#include "Niflect/NiflectType.h"
#include "Accessor.h"

using namespace RwTree;

class CPropertyEditorSystem;

//class CPropertyBuilder
//{
//public:
//	CPropertyBuilder(CPropertyEditorSystem* sys);
//	void CPropertyEditorSystem::BuildTree()
//	{
//
//	}
//
//private:
//	CPropertyEditorSystem* m_sys;
//};

class CBuildBranchContext
{
public:
	CBuildBranchContext(CPropertyEditorSystem* sys, Niflect::CNiflectType* type, CRwNode* rw)
		: m_sys(sys)
		, m_type(type)
		, m_rw(rw)
	{
	}
	CPropertyEditorSystem* m_sys;
	CRwNode* m_rw;
	Niflect::CNiflectType* m_type;
};