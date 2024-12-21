#include "Widget/ContentExplorer/QContentView.h"
#include "Base/AssetCreatorDefinition.h"
#include "Niflect/Util/SystemUtil.h"
#include "Niflect/Util/StringUtil.h"

namespace WishingQt
{
	QContentView::QContentView(QWidget* parentWidget)
		: inherited(parentWidget)
	{
		Niflect::TArrayNif<Niflect::CString> vecFound;
		auto searchPath = NiflectUtil::ResolvePath(AssetCreatorDefinition::DirPath::ExampleAsset);
		searchPath = NiflectUtil::ConvertToSearchPath(NiflectUtil::ConcatPath(searchPath, "Document"));
		NiflectUtil::SearchFiles(searchPath, "*", vecFound);
		for (auto& it : vecFound)
		{
			auto item = new QTreeWidgetItem;
			item->setText(0, it.c_str());
			this->addTopLevelItem(item);
		}
	}
}