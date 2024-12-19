#include "Widget/Creator/QCreatorWindow.h"
#include "Widget/ContentExplorer/QContentView.h"
#include "QToolBar"
#include "QToolTip"
#include "QBoxLayout"
#include "QPushButton"

namespace WishingQt
{
	QCreatorWindow::QCreatorWindow(QWidget* parentWidget)
		: inherited(parentWidget)
	{
		auto wdgCentral = new QWidget(this);
		this->setCentralWidget(wdgCentral);
		auto mainLayout = new QHBoxLayout(wdgCentral);

		m_contentView = new QContentView(this);
		mainLayout->addWidget(m_contentView);

		auto panelRight = new QWidget(this);
		auto rightLayout = new QVBoxLayout(panelRight);
		mainLayout->addWidget(panelRight);

		auto btnDebug = new QPushButton("Debug Create", this);
		QObject::connect(btnDebug, &QPushButton::clicked, []()
			{
				QToolTip::showText(QCursor::pos(), "Debug Create");
			});
		rightLayout->addWidget(btnDebug);

		auto toolBar = this->addToolBar("Default");
		auto actDebug = new QAction("Nihao");
		QObject::connect(actDebug, &QAction::triggered, [this]()
			{
				QToolTip::showText(QCursor::pos(), "nihao");
			});
		toolBar->addAction(actDebug);
	}
}