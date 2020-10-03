#include "decisionwidget.h"

DecisionWidget::DecisionWidget(QWidget* parent):QTableView(parent)
{
    this->model = new DecisionModel(0,this);
    this->setModel(model);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void DecisionWidget::appendQuestion()
{
    model->appendQuestion();
}

void DecisionWidget::setDecisions(QStringList decisionList)
{
    model->setDecisions(decisionList);
    double rating = calculateRating();
    int resultRow = model->rowCount();

    model->insertRow(resultRow);
    model->setHeaderData(resultRow,Qt::Vertical,tr("Результат"));
    QString resultValue = tr("Ваша оценка %1(%2%)").arg(qRound(rating * 10)).arg(rating * 100);

    this->setSpan(resultRow,0,1,3);
    QModelIndex resultIndex = model->index(resultRow,0);
    model->setData(resultIndex,resultValue);
}

void DecisionWidget::setAnswer(int row, QString answer)
{
    model->setAnswer(row,answer);
}


double DecisionWidget::calculateRating()
{
    int correctAnswersCount = 0;
    int wrongAnswersCount = 0;
    for (int i = 0; i < model->rowCount();i++) {
        QModelIndex statusIndex = model->index(i,2);
        QString statusData = model->data(statusIndex).toString();
        if(statusData == tr("Верно"))
        {
            correctAnswersCount +=1;
        }
        else{
            wrongAnswersCount+=1;
        }
    }
    double Rating = (double)correctAnswersCount/(correctAnswersCount + wrongAnswersCount);
    return Rating;
}
