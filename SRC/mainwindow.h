#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QFileSystemModel>
#include <iostream>
#include<QPainter>
#include<vector>
#include <algorithm>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include<list>
#include <QDebug>
#include "LinkedList.h"
//#include "annotation.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct coords {
        int x,y;
    };


    std::vector<int> allCoords;

    int clicks = 0;

    int x1;

    int y1;

    int aWidth;

    int aHeight;

    int type;

    std:: vector<QPolygon> Triangles;

    std:: vector<QPolygon> Squares;

    std:: vector<QPolygon> Trapeziums;

    coords triangle[3];

    coords square[4];

    coords trap[4];

    std::vector<coords> PolyPoints;

    std:: vector<QPolygon> Polygons;

private slots:

    void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;


    virtual void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_actionOpen_triggered();

    void on_pushButton_3_clicked();

    void editShapes(int index1,int index2,std::string type,int x, int y);

    void checkShape(std::vector<QPolygon> Shape,  int x, int y);

    void ShowContextMenu(const QPoint&);

    void copyItem();

    void deleteItem();

    void pasteItem();

    void setMoving();


    QPolygon moveItem(std::vector<QPolygon> Shape,int x, int y);

    void drawItem();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void copyShape(std:: vector<QPolygon>);

    QPolygon resizeShape(QPolygon Shape,double diff);

    void setResize();

    void reloadImage(QString imgPath);

    QPolygon assignShape(coords Shape[],int size);

    void on_btn_OpenClass_clicked();

    void on_btn_AddClass_clicked();

    void on_btn_RemoveClass_clicked();

    void on_btn_ModifyClass_clicked();

    void on_btn_SortList_clicked();

    void on_actionSave_triggered();

    void clearShapes();

    void saveAnnotations();

    QPolygon loadShapes(QStringList data, int count, int size);

private:

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QFileSystemModel *dirModel;
    QString classFilePath;
    QString annotationFilePath;

    void updateFile();
    void addClassToLW();
};
#endif // MAINWINDOW_H

