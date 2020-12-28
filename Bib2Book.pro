#-------------------------------------------------
#
# Project created by QtCreator 2019-11-23T14:04:18
#
#-------------------------------------------------

QT       += core gui
QT       += charts
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bib2Book
TEMPLATE = app

RC_ICONS = icons/app_icon.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_NO_CAST_FROM_ASCII

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += c++11

TRANSLATIONS += \
             Bib2Book_en.ts\
             Bib2Book_cn.ts

CODECFORTR = utf-8 #or gbk
#DEFAULTCODEC = utf-8
#CODEC = utf-8

SOURCES += \
        main.cpp \
        view/mainwindow.cpp \
        model/project.cpp \
        view/workingarea.cpp \
        view/frame.cpp \
        view/titlebar.cpp

HEADERS += \
        view/data.h \
        view/mainwindow.h \
        model/project.h \
        model/structdefinition.h \
        model/constraints.h \
        view/workingarea.h \
        view/frame.h \
        view/titlebar.h

FORMS += \
        view/mainwindow.ui \
        view/workingarea.ui

INCLUDEPATH += $$PWD/model
INCLUDEPATH += $$PWD/view

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

