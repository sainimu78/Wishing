#include "Creator/QCreatorWindow.h"
#include "ContentExplorer/QContentView.h"

namespace QtWishing
{
	QCreatorWindow::QCreatorWindow(QWidget* parentWidget)
		: inherited(parentWidget)
	{
		m_contentView = new QContentView(this);

		this->setCentralWidget(m_contentView);
	}
}