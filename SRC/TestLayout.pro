QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BinarySearch.cpp \
    LinkedList.cpp \
    QuickSort.cpp \
    annotation.cpp \
    itemclass.cpp \
    main.cpp \
    mainwindow.cpp \
    mythread.cpp \
    polygonclass.cpp \
    shapeclass.cpp \
    #Tests/project-tests.cpp \

HEADERS += \
    LinkedList.h \
    annotation.h \
    itemclass.h \
    mainwindow.h \
    mythread.h \
    polygonclass.h \
    shapeclass.h

FORMS += \
    mainwindow.ui

macx{
INCLUDEPATH += "/usr/local/Cellar/boost/1.72.0/include"
LIBS += -L"/usr/local/Cellar/boost/1.72.0/lib"
}

LIBS += -lboost_unit_test_framework

UI_DIR = $$PWD


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
