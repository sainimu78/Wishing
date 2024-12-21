#pragma once
#include "QTreeWidget"

namespace WishingQt
{
	class QContentView : public QWidget
	{
		typedef QWidget inherited;
	public:
		QContentView(QWidget* parentWidget);

	private:
		QTreeWidget* m_tree;
	};
}