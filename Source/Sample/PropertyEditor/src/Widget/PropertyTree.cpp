#include "Widget/PropertyTree.h"
#include "PropertyEditorSystem.h"

QPropertyTree::QPropertyTree(QWidget* parentWidget)
	: inherited(parentWidget)
	, m_sys(NULL)
{

}
void QPropertyTree::Init(CPropertyEditorSystem* sys)
{
	m_sys = sys;
}
void QPropertyTree::BuildFromInstance(CPropertyNode* parentProp, Niflect::CNiflectType* type, Niflect::InstanceType* instance)
{
	auto accessorType = GetAccessorType(type);
	auto prop = m_sys->FindCreateBoundProperty(accessorType);
	parentProp->AddNode(prop);
}
void QPropertyTree::BuildSection(Niflect::CNiflectType* type, Niflect::InstanceType* instance)
{

}