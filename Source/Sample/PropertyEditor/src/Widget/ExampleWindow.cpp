#include "Widget/ExampleWindow.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include "Util/QtUtil.h"
#include "Widget/PropertyTree.h"
#include "PropertyEditorSystem.h"

using namespace RwTree;

QExampleWindow::QExampleWindow(QWidget* parentWidget)
	: inherited(parentWidget)
	, m_cobCollection(NULL)
	, m_propTree(NULL)
	, m_sys(NULL)
{
	auto wdgCentral = new QWidget(this);
	this->setCentralWidget(wdgCentral);
	auto mainLayout = new QHBoxLayout(wdgCentral);

	auto cobCollection = new QComboBox(this);
	QObject::connect(cobCollection, &QComboBox::currentTextChanged, [this]()
		{
			auto& type = m_vecType[m_cobCollection->currentIndex()];
			m_dummy = Niflect::NiflectTypeMakeShared<void*>(type);
			CRwNode rw;
			type->SaveInstanceToRwNode(m_dummy.Get(), &rw);
			auto prop = CreatePropertyBranch(CPropertyBranchContext(m_sys, type, &rw));
			DebugPrintPropertyRecurs(prop.Get(), 0);
			printf("");
			//m_propTree->BuildFromInstance(m_propTree->GetRoot(), type, m_dummy.Get());
		});
	mainLayout->addWidget(cobCollection);
	m_cobCollection = cobCollection;

	m_propTree = new QPropertyTree(this);
	mainLayout->addWidget(m_propTree);
}
void QExampleWindow::Init(CPropertyEditorSystem* sys)
{
	m_sys = sys;
	m_propTree->Init(sys);
}
void QExampleWindow::BuildUi(const Niflect::CNiflectTable* table)
{
	for (uint32 idx = 0; idx < table->GetTypesCount(); ++idx)
	{
		auto type = table->GetTypeByIndex(idx);
		if (type->GetNata() != NULL)
		{
			m_vecType.push_back(type);
			m_cobCollection->addItem(CStringToQString(type->GetTypeName()));
		}
	}
}