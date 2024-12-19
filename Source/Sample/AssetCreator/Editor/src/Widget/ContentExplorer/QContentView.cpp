#include "Widget/ContentExplorer/QContentView.h"

namespace WishingQt
{
	QContentView::QContentView(QWidget* parentWidget)
		: inherited(parentWidget)
	{
		auto item = new QTreeWidgetItem;
		item->setText(0, "nihao");
		this->addTopLevelItem(item);
	}
}