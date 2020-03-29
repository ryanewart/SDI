#include "mainwindow.h"
#include "main.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //ptr = &w;
    w.show();
    return a.exec();
    //Comment
}

