#pragma once
#include "QMainWindow"
#include "Creator/CreatorSystem.h"
#include "WishingEngine/Content/ContentSystem.h"

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
		void Init2(Wishing::CContentSystem* sys);

	private:
		QContentView* m_contentView;
		Wishing::CCreatorSystem* m_sys;
		Wishing::CContentSystem* m_sys2;
	};
}