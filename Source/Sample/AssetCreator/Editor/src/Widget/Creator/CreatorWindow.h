#pragma once
#include "QMainWindow"

namespace WishingQt
{
	class QContentView;

	class QCreatorWindow : public QMainWindow
	{
		typedef QMainWindow inherited;
	public:
		QCreatorWindow(QWidget* parentWidget = NULL);

	private:
		QContentView* m_contentView;
	};
}