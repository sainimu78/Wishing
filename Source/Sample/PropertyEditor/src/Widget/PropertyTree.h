#pragma once
#include "qwidget.h"

class CPropertyEditorSystem;

class QPropertyTree : public QWidget
{
	typedef QWidget inherited;
public:
	QPropertyTree(QWidget* parentWidget = NULL);
	void Init(CPropertyEditorSystem* sys);

private:
	CPropertyEditorSystem* m_sys;
};