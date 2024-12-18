#pragma once
#include "QTreeWidget"

namespace QtWishing
{
	class QContentView : public QTreeWidget
	{
		typedef QTreeWidget inherited;
	public:
		QContentView(QWidget* parentWidget);
	};
}