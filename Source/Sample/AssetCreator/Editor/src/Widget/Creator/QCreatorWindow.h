#pragma once
#include "QMainWindow"

namespace QtWishing
{
	class QContentView;

	class QCreatorWindow : public QMainWindow
	{
		typedef QMainWindow inherited;
	public:
		QCreatorWindow(QWidget* parentWidget = NULL);
		QContentView* m_contentView;
	};
}