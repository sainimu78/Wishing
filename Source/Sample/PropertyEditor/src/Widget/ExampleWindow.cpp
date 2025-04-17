#include "Widget/ExampleWindow.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include "Util/QtUtil.h"
#include "Widget/PropertyTree.h"

QExampleWindow::QExampleWindow(QWidget* parentWidget)
	: inherited(parentWidget)
	, m_cobCollection(NULL)
	, m_propTree(NULL)
{
	auto wdgCentral = new QWidget(this);
	this->setCentralWidget(wdgCentral);
	auto mainLayout = new QHBoxLayout(wdgCentral);

	auto cobCollection = new QComboBox(this);
	QObject::connect(cobCollection, &QComboBox::currentTextChanged, [this]()
		{
			auto& type = m_vecType[m_cobCollection->currentIndex()];
			m_propTree->BuildFromInstance(type, NULL);
		});
	mainLayout->addWidget(cobCollection);
	m_cobCollection = cobCollection;

	m_propTree = new QPropertyTree(this);
	mainLayout->addWidget(m_propTree);
}
void QExampleWindow::BuildUi(const Niflect::CNiflectTable* table)
{
	for (uint32 idx = 0; idx < table->GetTypesCount(); ++idx)
	{
		auto type = table->GetTypeByIndex(idx);
		m_vecType.push_back(type);
		m_cobCollection->addItem(CStringToQString(type->GetTypeName()));
	}
}