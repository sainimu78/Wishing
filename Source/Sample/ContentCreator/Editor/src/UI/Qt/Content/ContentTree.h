#pragma once
#include "qtreeview.h"
#include "qstandarditemmodel.h"
#include "WishingEngine/Content/ContentSystem.h"

namespace WishingQt
{
	//class QContentTree : public QWidget
	//{
	//	typedef QWidget inherited;
	//public:
	//	QContentTree(QWidget* parentWidget);

	//private:
	//	QTreeWidget* m_tree;
	//};
    
    class QContentTree : public QWidget
    {
        typedef QWidget inherited;
    public:
        QContentTree(QWidget* parentWidget);

    public:
        void Init(Wishing::CContentSystem* sys);

    private:
        void populateModel();
        void showContextMenu(const QPoint& pos);
        void addItem();

    private:
        QTreeView* m_treeView;
        QStandardItemModel* m_model;
        Wishing::CContentSystem* m_sys;
    };
}