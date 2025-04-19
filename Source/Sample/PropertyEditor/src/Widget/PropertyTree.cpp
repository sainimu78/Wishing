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