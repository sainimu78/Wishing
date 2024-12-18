#include "Widget/ContentExplorer/QContentView.h"

namespace QtWishing
{
	QContentView::QContentView(QWidget* parentWidget)
		: inherited(parentWidget)
	{
		auto item = new QTreeWidgetItem;
		item->setText(0, "nihao");
		this->addTopLevelItem(item);
	}
}