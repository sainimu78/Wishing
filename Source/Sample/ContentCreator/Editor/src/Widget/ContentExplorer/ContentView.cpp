#include "Widget/ContentExplorer/ContentView.h"
#include "Base/AssetCreatorDefinition.h"
#include "Niflect/Util/SystemUtil.h"
#include "Niflect/Util/StringUtil.h"
#include "QBoxLayout"
#include "Widget/Util/CoreUtil.h"

namespace WishingQt
{
	QContentView::QContentView(QWidget* parentWidget)
		: inherited(parentWidget)
	{
		auto mainLayout = new QVBoxLayout(this);
		m_tree = new QTreeWidget(this);
		mainLayout->addWidget(m_tree);

		Niflect::TArrayNif<Niflect::CString> vecFound;
		//auto searchPath = NiflectUtil::ConcatPath(AssetCreatorDefinition::DirPath::GetExampleAssetDirPath(), "Document");
		auto searchPath = AssetCreatorDefinition::DirPath::GetExampleAssetDirPath();
		NiflectUtil::CollectFiles(searchPath, NiflectUtil::CCollectingOption([&](const NiflectUtil::SCollectingContext& ctx)
			{
				auto filePath = NiflectUtil::ConcatPath(ctx.m_dirPath, ctx.m_fileName);
				vecFound.push_back(filePath);
			}).SetMaxDepth(0));
		for (auto& it : vecFound)
		{
			auto item = new QTreeWidgetItem;
			item->setText(0, CStringToQString(it));
			m_tree->addTopLevelItem(item);
		}

		m_tree->resizeColumnToContents(0);
	}
}