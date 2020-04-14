#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class saveThread : public QThread
{
    Q_OBJECT
public:
    saveThread();
    void run() override;

signals:
    void callSave();
public slots:

};

#endif // MYTHREAD_H

