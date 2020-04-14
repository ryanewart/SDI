#include "mythread.h"
#include <QtCore>
#include <QMutex>
#include <QDebug>

saveThread::saveThread()
{

}

void saveThread::run(){
    while (true) {
        emit callSave();
        qDebug() << "Thread sending save request \n";
        this->sleep(5);
    }
}
