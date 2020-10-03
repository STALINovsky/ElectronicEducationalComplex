#ifndef DECISIONMODEL_H
#define DECISIONMODEL_H

#include <QAbstractTableModel>
#include <QApplication>
#include <QPalette>

class DecisionModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DecisionModel(int questionsCount = 0,QObject *parent = nullptr);

    void setDecisions(QStringList decisionList);
    void setAnswer(int row,QString answer);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int row , int count , const QModelIndex & parent = QModelIndex ()) override;
    void appendQuestion();
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

protected:
    QList <QVector<QString>> tableItems;
    QVector <QString> verticalHeaderItems;
    QVector <QString> horizontalHeaderItems;
    int questionsCount = 0;

};

#endif // DECISIONMODEL_H
