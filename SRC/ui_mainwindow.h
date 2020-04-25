/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionFile;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionTest;
    QAction *actionRename;
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QSplitter *splitter;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QTreeView *treeView;
    QLabel *labelMainPic;
    QListWidget *listWidget;
    QLabel *label;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_OpenClass;
    QPushButton *btn_AddClass;
    QPushButton *btn_RemoveClass;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_SortList_3;
    QPushButton *btn_SortList;
    QPushButton *btn_ModifyClass;
    QPushButton *btn_SearchList;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1260, 900);
        actionFile = new QAction(MainWindow);
        actionFile->setObjectName(QString::fromUtf8("actionFile"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QString::fromUtf8("actionTest"));
        actionRename = new QAction(MainWindow);
        actionRename->setObjectName(QString::fromUtf8("actionRename"));
        actionRename->setVisible(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1110, 0, 120, 611));
        QFont font;
        font.setPointSize(18);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        splitter = new QSplitter(groupBox);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(4, 30, 111, 571));
        QFont font1;
        font1.setPointSize(14);
        splitter->setFont(font1);
        splitter->setOrientation(Qt::Vertical);
        pushButton = new QPushButton(splitter);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        splitter->addWidget(pushButton);
        pushButton_2 = new QPushButton(splitter);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        splitter->addWidget(pushButton_2);
        pushButton_3 = new QPushButton(splitter);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setText(QString::fromUtf8("Trapesium"));
        pushButton_3->setIconSize(QSize(12, 12));
        splitter->addWidget(pushButton_3);
        pushButton_4 = new QPushButton(splitter);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        splitter->addWidget(pushButton_4);
        pushButton_5 = new QPushButton(splitter);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        splitter->addWidget(pushButton_5);
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 680, 651, 171));
        labelMainPic = new QLabel(centralwidget);
        labelMainPic->setObjectName(QString::fromUtf8("labelMainPic"));
        labelMainPic->setGeometry(QRect(50, 20, 1021, 561));
        labelMainPic->setStyleSheet(QString::fromUtf8("border-style: solid;\n"
"border-width: 2px;\n"
"border-color: red;\n"
"border-radius: 2px;"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(680, 680, 581, 171));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 600, 321, 81));
        QFont font2;
        font2.setPointSize(18);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(680, 600, 211, 31));
        label_2->setFont(font2);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(680, 610, 581, 78));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btn_OpenClass = new QPushButton(layoutWidget);
        btn_OpenClass->setObjectName(QString::fromUtf8("btn_OpenClass"));

        horizontalLayout->addWidget(btn_OpenClass);

        btn_AddClass = new QPushButton(layoutWidget);
        btn_AddClass->setObjectName(QString::fromUtf8("btn_AddClass"));

        horizontalLayout->addWidget(btn_AddClass);

        btn_RemoveClass = new QPushButton(layoutWidget);
        btn_RemoveClass->setObjectName(QString::fromUtf8("btn_RemoveClass"));

        horizontalLayout->addWidget(btn_RemoveClass);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btn_SortList_3 = new QPushButton(layoutWidget);
        btn_SortList_3->setObjectName(QString::fromUtf8("btn_SortList_3"));

        verticalLayout->addWidget(btn_SortList_3);

        btn_SortList = new QPushButton(layoutWidget);
        btn_SortList->setObjectName(QString::fromUtf8("btn_SortList"));

        verticalLayout->addWidget(btn_SortList);


        horizontalLayout->addLayout(verticalLayout);

        btn_ModifyClass = new QPushButton(layoutWidget);
        btn_ModifyClass->setObjectName(QString::fromUtf8("btn_ModifyClass"));

        horizontalLayout->addWidget(btn_ModifyClass);

        btn_SearchList = new QPushButton(layoutWidget);
        btn_SearchList->setObjectName(QString::fromUtf8("btn_SearchList"));

        horizontalLayout->addWidget(btn_SearchList);

        MainWindow->setCentralWidget(centralwidget);
        layoutWidget->raise();
        labelMainPic->raise();
        groupBox->raise();
        treeView->raise();
        listWidget->raise();
        label->raise();
        label_2->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1260, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionRename);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionFile->setText(QCoreApplication::translate("MainWindow", "File", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save As...", nullptr));
        actionTest->setText(QCoreApplication::translate("MainWindow", "Test", nullptr));
        actionRename->setText(QCoreApplication::translate("MainWindow", "Rename", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Triangle", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Square", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Polygon", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        labelMainPic->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Image Selector", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Class Selector", nullptr));
        btn_OpenClass->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        btn_AddClass->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        btn_RemoveClass->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        btn_SortList_3->setText(QCoreApplication::translate("MainWindow", "Sort DESC", nullptr));
        btn_SortList->setText(QCoreApplication::translate("MainWindow", "Sort ASC", nullptr));
        btn_ModifyClass->setText(QCoreApplication::translate("MainWindow", "Modify", nullptr));
        btn_SearchList->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
