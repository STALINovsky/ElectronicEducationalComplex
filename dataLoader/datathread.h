#ifndef TESTTHREAD_H
#define TESTTHREAD_H
#include <QThread>
#include <dataLoader/dataloader.h>

class DataLoader : public ClientSocket
{
    Q_OBJECT
public:
    DataLoader();
signals:
    void testListLoaded(QStringList testList);
    void testLoaded(QString name);
    void decisionLoaded(QString decisionData);
    void lecturesLoaded();
    void labsLoaded();

public slots:
    void loadTestList();
    void loadTest(QString testName);
    void refreshLectures();
    void refreshLabs();
    void loadDecision(QString answerData);
private slots:
};

#endif // TESTTHREAD_H
