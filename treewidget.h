#ifndef TREEWIDGET_H
#define TREEWIDGET_H
#include <QTreeWidget>
#include <QDir>
#include <QDebug>

class TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = nullptr);

    void load_data(QString path);
    void add_all_child(QTreeWidgetItem* item, QString currentPath);
};

#endif // TREEWIDGET_H
