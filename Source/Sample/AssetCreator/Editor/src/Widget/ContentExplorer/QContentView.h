#pragma once
#include "QTreeWidget"

namespace WishingQt
{
	class QContentView : public QTreeWidget
	{
		typedef QTreeWidget inherited;
	public:
		QContentView(QWidget* parentWidget);
	};
}