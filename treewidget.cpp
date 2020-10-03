#include "treewidget.h"

TreeWidget::TreeWidget(QWidget* parent):QTreeWidget(parent)
{

}

void TreeWidget::load_data(QString path)
{
    QDir dir(path);
    dir.setFilter(QDir::Dirs|QDir::NoDot|QDir::NoDotDot);
    QStringList dirList = dir.entryList();
    qDebug() << dir.path();

    foreach(QString catalogName, dirList)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0,catalogName);
        item->setToolTip(0,catalogName);
        this->addTopLevelItem(item);

        QString dataPath = path+"/"+catalogName;
        QStringList data;
        data.append(dataPath);
        data.append(dataPath+".htm");

        item->setData(0, Qt::ItemDataRole::UserRole, data);

        QString newCurrentPath = path+"/"+catalogName;
        add_all_child(item,newCurrentPath);
    }
}

void TreeWidget::add_all_child(QTreeWidgetItem* item, QString currentPath)
{
    QDir dir(currentPath);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList dirList = dir.entryList();
    foreach (QString dirName, dirList) {
        if(dirName.contains(QRegExp("(.files|TestItem|AboutTest)")))
        {
            dirList.removeOne(dirName);
        }
    }

    QList<QTreeWidgetItem*> childList;
    foreach(QString childName,dirList)
    {
        QTreeWidgetItem* childItem = new QTreeWidgetItem;

        childItem->setText(0,childName);
        childItem->setToolTip(0,childName);
        childList.append(childItem);

        QString newCurrentPath = currentPath+"/"+childName;
        QStringList data;
        data.append(newCurrentPath);
        data.append(childName+".htm");

        childItem->setData(0, Qt::ItemDataRole::UserRole, data);
        add_all_child(childItem,newCurrentPath);
    }
    item->addChildren(childList);
}

