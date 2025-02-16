#pragma once
#include "QMainWindow"
#include "Creator/CreatorSystem.h"
#include "WishingEngine/Content/ContentSystem.h"

namespace WishingQt
{
	class QContentTree;

	class QCreatorWindow : public QMainWindow
	{
		typedef QMainWindow inherited;
	public:
		QCreatorWindow(QWidget* parentWidget = NULL);

	public:
		void Init(Wishing::CCreatorSystem* sys);
		void Init2(Wishing::CContentSystem* sys);

	private:
		QContentTree* m_contentView;
		Wishing::CCreatorSystem* m_sys;
		Wishing::CContentSystem* m_sys2;
	};
}