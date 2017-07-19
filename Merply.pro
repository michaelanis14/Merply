#-------------------------------------------------
# File: Merply.pro
# Created on: Wed Feb 18 2015
# Copyright (C) 2015 Merply - Michael Bishara e.U.
#-------------------------------------------------

QT       += core gui printsupport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent

TARGET = MERPLY
TEMPLATE = app

INCLUDEPATH +=  View\
                Model\
                Controller \

SOURCES += main.cpp

include(View/View.pri)
include(Model/Model.pri)
include(Controller/Controller.pri)
include(QtRPT/QtRpt.pri)

#win32: LIBS += -L$$PWD/lib/TurboActivate/win32/ \
#    -lTurboActivate
#else:unix: LIBS += -L$$PWD/lib/TurboActivate/amd64/ \
#    -lTurboActivate

release:DESTDIR = release
release:OBJECTS_DIR = release/.obj
release:MOC_DIR = release/.moc
release:RCC_DIR = release/.rcc
release:UI_DIR = release/.ui

debug:DESTDIR = debug
debug:OBJECTS_DIR = debug/.obj
debug:MOC_DIR = debug/.moc
debug:RCC_DIR = debug/.rcc
debug:UI_DIR = debug/.ui

#CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

#CONFIG += static
#CONFIG   -= x86_64
# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
#QMAKE_CXXFLAGS_RELEASE *= -O2

!contains(DEFINES,NO_BARCODE) {
LIBS += -L$${DESTDIR}/lib -lQtZint
}



RESOURCES += \
    resources/resources.qrc



macx: LIBS += -L$$PWD/../Build/debug/lib/mySQL/lib/ -lmysqlcppconn.7.1.1.8

INCLUDEPATH += $$PWD/../Build/debug/lib/mySQL/include
DEPENDPATH += $$PWD/../Build/debug/lib/mySQL/include



macx: LIBS += -L$$PWD/../../../../../usr/local/Cellar/mysql/5.7.17/lib/ -lmysqlclient.20

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/mysql/5.7.17/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/mysql/5.7.17/include



macx: LIBS += -L$$PWD/../../../../../Users/michaelbishara/Qt5.8.0/5.8/clang_64/plugins/sqldrivers/ -lqsqlmysql

INCLUDEPATH += $$PWD/../../../../../Users/michaelbishara/Qt5.8.0/5.8/clang_64/plugins/sqldrivers
DEPENDPATH += $$PWD/../../../../../Users/michaelbishara/Qt5.8.0/5.8/clang_64/plugins/sqldrivers


win32: LIBS += -L'C:/Program Files (x86)/MySQL/MySQLConnector.C6.1/lib/' -llibmysql

INCLUDEPATH += 'C:/Program Files (x86)/MySQL/MySQLConnector.C6.1/include'
DEPENDPATH += 'C:/Program Files (x86)/MySQL/MySQLConnector.C6.1/include'


