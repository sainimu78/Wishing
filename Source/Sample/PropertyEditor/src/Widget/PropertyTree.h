#pragma once
#include "qwidget.h"
#include "Niflect/NiflectType.h"

class QPropertyTree : public QWidget
{
	typedef QWidget inherited;
public:
	QPropertyTree(QWidget* parentWidget = NULL);

public:
	void BuildFromInstance(Niflect::CNiflectType* type, void* instance);
};