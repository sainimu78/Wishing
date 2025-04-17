#include "Widget/ExampleWindow.h"
#include "qboxlayout.h"
#include "qpushbutton.h"

QExampleWindow::QExampleWindow(QWidget* parentWidget)
	: inherited(parentWidget)
{
	auto wdgCentral = new QWidget(this);
	this->setCentralWidget(wdgCentral);
	auto mainLayout = new QHBoxLayout(wdgCentral);

	auto btnDebug = new QPushButton("Debug Create", this);
	mainLayout->addWidget(btnDebug);
}
