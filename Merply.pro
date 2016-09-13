#-------------------------------------------------
# File: Merply.pro
# Created on: Wed Feb 18 2015
# Copyright (C) 2015 Merply - Michael Bishara e.U.
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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



CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

CONFIG += static
CONFIG   -= x86_64
# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
#QMAKE_CXXFLAGS_RELEASE *= -O2





unix: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/libcouchbase/2.5.4/lib/ -lcouchbase

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/libcouchbase/2.5.4/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/libcouchbase/2.5.4/include

RESOURCES += \
    resources/resources.qrc
