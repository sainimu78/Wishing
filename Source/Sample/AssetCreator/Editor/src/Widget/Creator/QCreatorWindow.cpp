#include "Creator/QCreatorWindow.h"
#include "ContentExplorer/QContentView.h"
#include "QToolBar"
#include "QToolTip"

namespace QtWishing
{
	QCreatorWindow::QCreatorWindow(QWidget* parentWidget)
		: inherited(parentWidget)
	{
		m_contentView = new QContentView(this);

		this->setCentralWidget(m_contentView);

		auto toolBar = this->addToolBar("Default");
		auto actDebug = new QAction("Nihao");
		QObject::connect(actDebug, &QAction::triggered, [this]()
			{
				QToolTip::showText(QCursor::pos(), "nihao");
			});
		toolBar->addAction(actDebug);
	}
}