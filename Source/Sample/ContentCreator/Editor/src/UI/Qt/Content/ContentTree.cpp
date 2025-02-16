#include "UI/Qt/Content/ContentTree.h"
#include "Base/AssetCreatorDefinition.h"
#include "Niflect/Util/SystemUtil.h"
#include "Niflect/Util/StringUtil.h"
#include "QBoxLayout"
#include "UI/Qt/Util/CoreUtil.h"
#include "qmenu.h"
#include "qinputdialog.h"
#include "WishingEngine/Content/ContentEditingScope.h"

namespace WishingQt
{
	//QContentTree::QContentTree(QWidget* parentWidget)
	//	: inherited(parentWidget)
	//{
	//	auto mainLayout = new QVBoxLayout(this);
	//	m_tree = new QTreeWidget(this);
	//	mainLayout->addWidget(m_tree);

	//	Niflect::TArrayNif<Niflect::CString> vecFound;
	//	//auto searchPath = NiflectUtil::ConcatPath(AssetCreatorDefinition::DirPath::GetExampleAssetDirPath(), "Document");
	//	auto searchPath = AssetCreatorDefinition::DirPath::GetExampleAssetDirPath();
	//	NiflectUtil::CollectFiles(searchPath, NiflectUtil::CCollectingOption([&](const NiflectUtil::SCollectingContext& ctx)
	//		{
	//			auto filePath = NiflectUtil::ConcatPath(ctx.m_dirPath, ctx.m_fileName);
	//			vecFound.push_back(filePath);
	//		}).SetMaxDepth(0));
	//	for (auto& it : vecFound)
	//	{
	//		auto item = new QTreeWidgetItem;
	//		item->setText(0, CStringToQString(it));
	//		m_tree->addTopLevelItem(item);
	//	}

	//	m_tree->resizeColumnToContents(0);
	//}


    using namespace Wishing;

    QContentTree::QContentTree(QWidget* parentWidget)
        : inherited(parentWidget)
        , m_sys(NULL)
    {
        // ����QTreeView
        m_treeView = new QTreeView(this);

        // ����ģ��
        m_model = new QStandardItemModel(this);
        m_model->setHorizontalHeaderLabels(QStringList() << "Name");

        // ����ģ�͵�QTreeView
        m_treeView->setModel(m_model);
        m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);  // ���������Ĳ˵�����

        // �����źźͲ�
        connect(m_treeView, &QTreeView::customContextMenuRequested, this, &QContentTree::showContextMenu);

        // ����
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(m_treeView);
        //setLayout(layout);

        this->setWindowTitle("QTreeView Right Click Menu Example");
        //resize(400, 300);

        // ��ʼ����
        this->populateModel();
    }
    void QContentTree::Init(CContentSystem* sys)
    {
        m_sys = sys;
    }
    void QContentTree::populateModel() {
        // ��������Ŀ
        QStandardItem* rootItem = m_model->invisibleRootItem();

        // ��ӽڵ�
        QStandardItem* fruitsItem = new QStandardItem("Fruits");
        QStandardItem* vegetablesItem = new QStandardItem("Vegetables");

        rootItem->appendRow(fruitsItem);
        rootItem->appendRow(vegetablesItem);
    }
    void QContentTree::showContextMenu(const QPoint& pos) {
        QMenu contextMenu("Context Menu", this);

        QAction* addItemAction = contextMenu.addAction("Add Item");
        QObject::connect(addItemAction, &QAction::triggered, this, &QContentTree::addItem);

        contextMenu.exec(m_treeView->viewport()->mapToGlobal(pos));
    }

    void QContentTree::addItem() {
        // ��ȡ�û����������
        bool ok;
        QString itemName = QInputDialog::getText(this, "Add Item",
            "Item Name:", QLineEdit::Normal,
            "", &ok);
        if (ok && !itemName.isEmpty()) {
            //// ��ȡѡ�е�����
            //QModelIndex selectedIndex = m_treeView->currentIndex();

            //// ���û��ѡ���κ����ӵ���
            //QStandardItem* parentItem;
            //if (selectedIndex.isValid()) {
            //    parentItem = m_model->itemFromIndex(selectedIndex);
            //}
            //else {
            //    parentItem = m_model->invisibleRootItem();
            //}

            //// ����µ���Ŀ
            //QStandardItem* newItem = new QStandardItem(itemName);
            //parentItem->appendRow(newItem);


            CContentEditingScope scope(m_sys);
            scope.AddFileNode(WishingQt::QStringToCString(itemName));
        }
    }
}