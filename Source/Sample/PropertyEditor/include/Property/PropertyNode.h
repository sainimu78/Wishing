#pragma once
#include "Niflect/Base/SharedPtr.h"
#include "Niflect/Base/Array.h"
#include "Niflect/Base/String.h"
#include "Niflect/NiflectAccessor.h"
#include "qwidget.h"
#include "PropertyBranchContext.h"
#include "Niflect/Default/DefaultMacroTag.h"

class CPropertyNode;
using CSharedPropertyNode = Niflect::TSharedPtr<CPropertyNode>;

class CPropertyNode
{
public:
	CPropertyNode()
		: m_accessorType(NULL)
	{

	}
	void InitAccessorType(Niflect::CNiflectType* accessorType)
	{
		m_accessorType = accessorType;
	}
	void InitName(const Niflect::CString& name)
	{
		m_name = name;
	}
	void AddNode(const CSharedPropertyNode& node)
	{
		m_vecNode.push_back(node);
	}

public:
	virtual void BuildNode(const CPropertyBranchContext& ctx) = 0;
	virtual CRwNode* GetRwData() const { return NULL; }

public:
	Niflect::CNiflectType* m_accessorType;
	Niflect::TArray<CSharedPropertyNode> m_vecNode;
	Niflect::CString m_name;

private:
};

class CPropertyItem: public CPropertyNode
{
public:
	virtual CRwNode* GetRwData() const override { return m_rw.Get(); }

protected:
	CSharedRwNode m_rw;
};

NIF_T()
class CPropertyGroup : public CPropertyNode
{
public:
	virtual void BuildNode(const CPropertyBranchContext& ctx) override;

private:
	void BuildFields(const CPropertyBranchContext& ctx, Niflect::CNiflectType* type);
};

NIF_T()
class CFloatProperty : public CPropertyItem
{
public:
	virtual void BuildNode(const CPropertyBranchContext& ctx) override;
};