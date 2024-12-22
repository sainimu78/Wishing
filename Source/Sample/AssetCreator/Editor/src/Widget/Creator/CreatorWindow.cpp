#include "Widget/Creator/CreatorWindow.h"
#include "Widget/ContentExplorer/ContentView.h"
#include "QToolBar"
#include "QToolTip"
#include "QBoxLayout"
#include "QPushButton"
#include "Project/Project.h"
#include "Base/AssetCreatorDefinition.h"
#include "Niflect/Util/StringUtil.h"

namespace WishingQt
{
	QCreatorWindow::QCreatorWindow(QWidget* parentWidget)
		: inherited(parentWidget)
	{
		auto wdgCentral = new QWidget(this);
		this->setCentralWidget(wdgCentral);
		auto mainLayout = new QHBoxLayout(wdgCentral);

		m_contentView = new QContentView(this);
		mainLayout->addWidget(m_contentView);

		auto panelRight = new QWidget(this);
		auto rightLayout = new QVBoxLayout(panelRight);
		mainLayout->addWidget(panelRight);

		auto btnDebug = new QPushButton("Debug Create", this);
		QObject::connect(btnDebug, &QPushButton::clicked, []()
			{
				auto fileName = Niflect::CString("DefaultProject") + AssetCreatorDefinition::FileExt::Project;
				auto filePath = NiflectUtil::ConcatPath(AssetCreatorDefinition::DirPath::GetExampleAssetDirPath(), fileName);
				Wishing::CreateProject(filePath);
				QToolTip::showText(QCursor::pos(), "Debug Create");
			});
		rightLayout->addWidget(btnDebug);

		auto toolBar = this->addToolBar("Default");
		auto actDebug = new QAction("Nihao");
		QObject::connect(actDebug, &QAction::triggered, [this]()
			{
				QToolTip::showText(QCursor::pos(), "nihao");
			});
		toolBar->addAction(actDebug);
	}
}