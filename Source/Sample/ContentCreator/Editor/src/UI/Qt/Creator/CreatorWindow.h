#pragma once
#include "QMainWindow"
#include "Creator/CreatorSystem.h"

namespace WishingQt
{
	class QContentView;

	class QCreatorWindow : public QMainWindow
	{
		typedef QMainWindow inherited;
	public:
		QCreatorWindow(QWidget* parentWidget = NULL);

	public:
		void Init(Wishing::CCreatorSystem* sys);

	private:
		QContentView* m_contentView;
		Wishing::CCreatorSystem* m_sys;
	};
}