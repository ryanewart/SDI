#include "mainwindow.h"
#include "main.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //ptr = &w;
    w.show();
    return a.exec();
    //Comment
}
