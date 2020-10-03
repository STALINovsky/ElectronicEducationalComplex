#include "decisionmodel.h"


DecisionModel::DecisionModel(int questionsCount,QObject *parent)
    : QAbstractTableModel(parent)
{

    this->horizontalHeaderItems.resize(3);
    horizontalHeaderItems[0] = tr("Ваш ответ");
    horizontalHeaderItems[1] = tr("Правильный ответ");
    horizontalHeaderItems[2] = tr("Результат");

    this->verticalHeaderItems.resize(questionsCount);
    for(int i = 0 ;i < questionsCount;i++)
    {
        verticalHeaderItems[i] = tr("Вопрос")+QString::number(i + 1);
    }

    for(int i = 0;i < questionsCount;i++)
    {
        tableItems.append(QVector<QString>(horizontalHeaderItems.length()));
    }

}

void DecisionModel::setDecisions(QStringList decisionList)
{
    for(int i = 0 ; i < decisionList.length();i++)
    {
        QModelIndex answerIndex = this->index(i,0);
        QModelIndex decisonIndex = this->index(i,1);
        QModelIndex resultIndex = this->index(i,2);

        QString decision = decisionList[i];
        QString answer = data(answerIndex).toString();

        QString resultValue;
        if(decision == answer)
        {
            resultValue = tr("Верно");
        }
        else {
            resultValue = tr("Неверно");
        }
        this->setData(decisonIndex,decisionList[i]);
        this->setData(resultIndex,resultValue);
    }

    QModelIndex topLeftIndex = this->index(0,0);
    QModelIndex bottomRightIndex = this->index(verticalHeaderItems.length() - 1,horizontalHeaderItems.length() - 1);

    emit dataChanged(topLeftIndex,bottomRightIndex);
}

void DecisionModel::setAnswer(int row, QString answer)
{
    QModelIndex index = this->index(row,0);
    this->setData(index,answer);
}

int DecisionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return verticalHeaderItems.length();
}

int DecisionModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return horizontalHeaderItems.length();
}

QVariant DecisionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        int row = index.row();
        int column = index.column();

        return tableItems[row][column];
    }
    else if(role == Qt::BackgroundRole)
    {
        QModelIndex resultIndex = this->index(index.row(),2);
        if(data(resultIndex) == tr("Верно"))
        {
            return QBrush(Qt::green);
        }
        else if(data(resultIndex) == tr("Неверно")) {
            return QBrush(Qt::red);
        }
    }
    return QVariant();
}

bool DecisionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        int row = index.row();
        int column = index.column();

        tableItems[row][column] = value.toString();
        emit dataChanged(index, index);
    }
    return false;
}

Qt::ItemFlags DecisionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool DecisionModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    if (count < 1 || row < 0 || row > verticalHeaderItems.count())
        return false;
    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int i = 0; i < count;i++) {
        tableItems.insert(row + i,QVector<QString>(horizontalHeaderItems.length()));
    }

    endInsertRows();
    return true;
}


void DecisionModel::appendQuestion()
{
    insertRow(this->verticalHeaderItems.length());
    verticalHeaderItems.insert(questionsCount,tr("Вопрос ") + QString::number(questionsCount + 1));
    ++questionsCount;
}

bool DecisionModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role!=Qt::EditRole)
    {
        return false;
    }

    QVector <QString>* header;
    if(orientation == Qt::Horizontal)
    {
        if(section > this->rowCount())
        {
            return false;
        }
        header = &this->horizontalHeaderItems;
    }
    else {
        if(section > this->columnCount())
        {
            return false;
        }
        header = &this->verticalHeaderItems;
    }
    header->insert(section,value.toString());
    return true;
}

QVariant DecisionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return horizontalHeaderItems[section];
    }
    else {
        return verticalHeaderItems[section];
    }
}
