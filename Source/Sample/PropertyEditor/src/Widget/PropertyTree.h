#pragma once
#include "qwidget.h"
#include "Niflect/NiflectType.h"
#include "Property/PropertyNode.h"

class CPropertyEditorSystem;

class QPropertyTree : public QWidget
{
	typedef QWidget inherited;
public:
	QPropertyTree(QWidget* parentWidget = NULL);
	void Init(CPropertyEditorSystem* sys);

public:
	void BuildFromInstance(CPropertyNode* parentProp, Niflect::CNiflectType* type, Niflect::InstanceType* instance);
	CPropertyGroup* GetRoot() { return &m_root; }

private:
	void BuildSection(Niflect::CNiflectType* type, Niflect::InstanceType* instance);

private:
	CPropertyEditorSystem* m_sys;
	CPropertyGroup m_root;
};