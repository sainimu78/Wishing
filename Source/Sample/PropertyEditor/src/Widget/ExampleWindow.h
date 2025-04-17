#pragma once
#include "qmainwindow.h"
#include "Niflect/NiflectTable.h"
#include "qcombobox.h"

class QPropertyTree;

class QExampleWindow : public QMainWindow
{
	typedef QMainWindow inherited;
public:
	QExampleWindow(QWidget* parentWidget = NULL);
	void BuildUi(const Niflect::CNiflectTable* table);

private:
	QComboBox* m_cobCollection;
	Niflect::TArray<Niflect::CNiflectType*> m_vecType;
	QPropertyTree* m_propTree;
};