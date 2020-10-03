#ifndef DECISIONWIDGET_H
#define DECISIONWIDGET_H
#include <QTableView>
#include <QHeaderView>
#include "decisionmodel.h"

class DecisionWidget : public QTableView
{
    Q_OBJECT
public:
    DecisionWidget(QWidget* parent = nullptr);
    void appendQuestion();

    void setDecisions(QStringList decisionList);
    void setAnswer(int row ,QString answer);

    double calculateRating();
private:
    DecisionModel* model;

};

#endif // DECISIONWIDGET_H
