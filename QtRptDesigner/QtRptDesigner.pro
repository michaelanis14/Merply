#-------------------------------------------------
#
# Project created by QtCreator 2012-03-29T16:09:02
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
    DEFINES += HAVE_QT5
}

TARGET = QtRptDesigner
VERSION = 1.5.5
DEFINES += VERSION=\\\"$$VERSION\\\"
TEMPLATE = app

include(../CommonFiles/CommonFiles_QtRptDesigner.pri)
include(../QtRPT/QtRPT.pri)
#include(SQLDiagram/SQLDiagram.pri)
unix: LIBS += -L$$PWD/../../../../../../../usr/local/Cellar/libcouchbase/2.5.4/lib/ -lcouchbase

INCLUDEPATH += $$PWD/../../../../../../../usr/local/Cellar/libcouchbase/2.5.4/include
DEPENDPATH += $$PWD/../../../../../../../usr/local/Cellar/libcouchbase/2.5.4/include

#DESTDIR = $${DEST_DIRECTORY}
CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release

release:DESTDIR = release
release:OBJECTS_DIR = release/.obj
release:MOC_DIR = release/.moc
release:RCC_DIR = release/.rcc
release:UI_DIR = release/.ui
}
debug:DESTDIR = debug
debug:OBJECTS_DIR = debug/.obj
debug:MOC_DIR = debug/.moc
debug:RCC_DIR = debug/.rcc
debug:UI_DIR = debug/.ui

!contains(DEFINES,NO_BARCODE) {
LIBS += -L$${DESTDIR}/lib -lQtZint
}

SOURCES += main.cpp\
    mainwindow.cpp \
    PageSettingDlg.cpp \
    ReportBand.cpp \
    RptContainer.cpp \
    EditFldDlg.cpp \
    aboutDlg.cpp \
    FldPropertyDlg.cpp \
    RepScrollArea.cpp \
    SettingDlg.cpp \
    overlay.cpp \
    TContainerLine.cpp \
    TContainerField.cpp \
    UndoCommands.cpp \
    XmlViewModel.cpp \
    ../Model/database.cpp

HEADERS  += mainwindow.h \
    PageSettingDlg.h \
    ReportBand.h \
    RptContainer.h \
    EditFldDlg.h \
    aboutDlg.h \
    FldPropertyDlg.h \
    RepScrollArea.h \
    SettingDlg.h \
    overlay.h \
    TContainerLine.h \
    TContainerField.h \
    UndoCommands.h \
    XmlViewModel.h \
    ../Model/database.h

FORMS    += mainwindow.ui \
    PageSettingDlg.ui \
    ReportBand.ui \
    EditFldDlg.ui \
    FldPropertyDlg.ui \
    RepScrollArea.ui \
    SettingDlg.ui

RESOURCES += \
    images.qrc

RC_FILE = QtRptDesigner.rc

TRANSLATIONS +=  \
    $$PWD/i18n/QtRprtDesigner_uk_UA.ts \
    $$PWD/i18n/QtRprtDesigner_sr_RS.ts \
    $$PWD/i18n/QtRprtDesigner_sr_RS@latin.ts \
    $$PWD/i18n/QtRprtDesigner_ar.ts \
    $$PWD/i18n/QtRprtDesigner_ka_GE.ts \
    $$PWD/i18n/QtRprtDesigner_pt_PT.ts \
    $$PWD/i18n/QtRprtDesigner_zh_CN.ts \
    $$PWD/i18n/QtRprtDesigner_es_ES.ts \
    $$PWD/i18n/QtRprtDesigner_fr_FR.ts \
    $$PWD/i18n/QtRprtDesigner_de_DE.ts \
    $$PWD/i18n/QtRprtDesigner_nl_BE.ts

OTHER_FILES += $$TRANSLATIONS

win32 {
    MOC_DIR = tmp-win32
    UI_DIR = tmp-win32
    UI_HEADERS_DIR = tmp-win32
    UI_SOURCES_DIR = tmp-win32
    OBJECTS_DIR = tmp-win32
    RCC_DIR = tmp-win32
}

unix {
    MOC_DIR = tmp-lin64
    UI_DIR = tmp-lin64
    UI_HEADERS_DIR = tmp-lin64
    UI_SOURCES_DIR = tmp-lin64
    OBJECTS_DIR = tmp-lin64
    RCC_DIR = tmp-lin64
}

#CONFIG += c++11
#CONFIG += app_bundle
#CONFIG -= debug_and_release debug_and_release_target




# Automatically build required translation files (*.qm)
all.depends = locale
#QMAKE_EXTRA_TARGETS += all

QMAKE_CXXFLAGS += -std=c++0x

TRANSLATION_TARGETS = $$replace(TRANSLATIONS, ".ts", ".qm")
locale.depends = $$TRANSLATION_TARGETS
QMAKE_EXTRA_TARGETS += locale

"%.qm".commands = lrelease -qm $@ $<
"%.qm".depends = "%.ts"
QMAKE_EXTRA_TARGETS += "%.qm"

PRE_TARGETDEPS += locale
