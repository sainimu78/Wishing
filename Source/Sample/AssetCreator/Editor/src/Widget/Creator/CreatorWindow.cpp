#include "Widget/Creator/CreatorWindow.h"
#include "Widget/ContentExplorer/ContentView.h"
#include "QToolBar"
#include "QToolTip"
#include "QBoxLayout"
#include "QPushButton"
#include "Project/Project.h"
#include "Base/AssetCreatorDefinition.h"
#include "Niflect/Util/StringUtil.h"
#include "Content/ContentBuilder.h"

namespace WishingQt
{
	QCreatorWindow::QCreatorWindow(QWidget* parentWidget)
		: inherited(parentWidget)
		, m_sys(NULL)
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

#ifdef CPP_SCRIPT_HOT_RELOADING_EXPERIMENT
		auto btnReloadScript = new QPushButton("Reload Script", this);
		QObject::connect(btnReloadScript, &QPushButton::clicked, [this]()
			{
				m_sys->ReloadScript();
			});
		rightLayout->addWidget(btnReloadScript);
#endif

		auto btnActivate = new QPushButton("Activate", this);
		QObject::connect(btnActivate, &QPushButton::clicked, [this]()
			{
				m_sys->AsyncActivate();
			});
		rightLayout->addWidget(btnActivate);

		auto btnCreateContent= new QPushButton("Create Content", this);
		QObject::connect(btnCreateContent, &QPushButton::clicked, [this]()
			{
				using namespace Wishing;
				CContentBuilder builder(m_sys->GetContentManager());
				
			});
		rightLayout->addWidget(btnCreateContent);

		auto toolBar = this->addToolBar("Default");
		auto actDebug = new QAction("Nihao");
		QObject::connect(actDebug, &QAction::triggered, [this]()
			{
				QToolTip::showText(QCursor::pos(), "nihao");
			});
		toolBar->addAction(actDebug);
	}
	void QCreatorWindow::Init(Wishing::CCreatorSystem* sys)
	{
		m_sys = sys;
	}
}