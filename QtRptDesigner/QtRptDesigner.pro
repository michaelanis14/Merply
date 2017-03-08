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

INCLUDEPATH +=  ../Model\
                ../Controller \
                ../View \
                ../View/structureViewBuilder\
                ../View/commonUI \
                ../View/commonUI/NavigationUI \
                ../View/VisualDesign \
                ../View/structureViewBuilder\
                ../View/permissionsUI \
                ../View/commonUI/MerplyTabel

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
    ../Model/database.cpp \
    ../Controller/accesscontroller.cpp \
    ../Controller/controller.cpp \
    ../Controller/printcontroller.cpp \
    ../View/commonUI/MerplyTabel/merplyquerysubfield.cpp \
    ../View/commonUI/MerplyTabel/merplyqueryui.cpp \
    ../View/commonUI/MerplyTabel/mtabelcombobox.cpp \
    ../View/commonUI/NavigationUI/navigationbtn.cpp \
    ../View/commonUI/NavigationUI/navigationeditui.cpp \
    ../View/commonUI/NavigationUI/navigationpageeditui.cpp \
    ../View/commonUI/NavigationUI/navigationui.cpp \
    ../View/commonUI/NavigationUI/pagestructureviewediteui.cpp \
    ../View/commonUI/NavigationUI/widgetsstructureviewediteui.cpp \
    ../View/commonUI/datefilterui.cpp \
    ../View/commonUI/erpcombobox.cpp \
    ../View/commonUI/expandbutton.cpp \
    ../View/commonUI/filepathui.cpp \
    ../View/commonUI/hcontrollers.cpp \
    ../View/commonUI/headerlabel.cpp \
    ../View/commonUI/hnavigationui.cpp \
    ../View/commonUI/logintabui.cpp \
    ../View/commonUI/merplytabelview.cpp \
    ../View/commonUI/merplytablecontrollers.cpp \
    ../View/commonUI/printview.cpp \
    ../View/commonUI/removebtn.cpp \
    ../View/commonUI/settingsctrlsui.cpp \
    ../View/commonUI/timelineui.cpp \
    ../View/permissionsUI/permissionfieldui.cpp \
    ../View/permissionsUI/permissionsui.cpp \
    ../View/structureViewBuilder/strctvieweditsubftblclmneq.cpp \
    ../View/structureViewBuilder/structureviewedit.cpp \
    ../View/structureViewBuilder/structurevieweditsubfeild.cpp \
    ../View/structureViewBuilder/structurevieweditsubfeildequation.cpp \
    ../View/structureViewBuilder/structurevieweditsubfeildtable.cpp \
    ../View/structureViewBuilder/structurevieweditsubfeildtablecolumn.cpp \
    ../View/structureViewBuilder/structurevieweditsubfeildtablecolumnquery.cpp \
    ../View/structureViewBuilder/structurevieweditsubfeildtablecolumnqueryui.cpp \
    ../View/structureViewBuilder/structureviewgroupsui.cpp \
    ../View/structureViewBuilder/structureviewseditui.cpp \
    ../View/createeditui.cpp \
    ../View/feildui.cpp \
    ../View/indexui.cpp \
    ../View/loginui.cpp \
    ../View/maindisplay.cpp \
    ../View/mainform.cpp \
    ../View/pageui.cpp \
    ../View/subfeildui.cpp \
    ../View/viewgroup.cpp \
    ../View/viewgroups.cpp \
    ../Model/database3.cpp \
    ../Model/merplyreporttablemodel.cpp \
    ../Model/model.cpp \
    ../Model/prsistance.cpp \
    ../Model/user.cpp \
    ../Model/couchbaselibmanager.cpp \
    ../View/commonUI/qtooltipper.cpp \
    ../View/structureViewBuilder/structureviewrefrence.cpp \
    ../View/structureViewBuilder/structureviewrefrencesubfield.cpp

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
    ../Model/database.h \
    ../Controller/accesscontroller.h \
    ../Controller/controller.h \
    ../Controller/printcontroller.h \
    ../View/commonUI/MerplyTabel/merplyquerysubfield.h \
    ../View/commonUI/MerplyTabel/merplyqueryui.h \
    ../View/commonUI/MerplyTabel/mtabelcombobox.h \
    ../View/commonUI/NavigationUI/navigationbtn.h \
    ../View/commonUI/NavigationUI/navigationeditui.h \
    ../View/commonUI/NavigationUI/navigationpageeditui.h \
    ../View/commonUI/NavigationUI/navigationui.h \
    ../View/commonUI/NavigationUI/pagestructureviewediteui.h \
    ../View/commonUI/NavigationUI/widgetsstructureviewediteui.h \
    ../View/commonUI/datefilterui.h \
    ../View/commonUI/erpcombobox.h \
    ../View/commonUI/expandbutton.h \
    ../View/commonUI/filepathui.h \
    ../View/commonUI/hcontrollers.h \
    ../View/commonUI/headerlabel.h \
    ../View/commonUI/hnavigationui.h \
    ../View/commonUI/logintabui.h \
    ../View/commonUI/merplytabelview.h \
    ../View/commonUI/merplytablecontrollers.h \
    ../View/commonUI/printview.h \
    ../View/commonUI/rangevalidator.h \
    ../View/commonUI/removebtn.h \
    ../View/commonUI/settingsctrlsui.h \
    ../View/commonUI/timelineui.h \
    ../View/permissionsUI/permissionfieldui.h \
    ../View/permissionsUI/permissionsui.h \
    ../View/structureViewBuilder/strctvieweditsubftblclmneq.h \
    ../View/structureViewBuilder/structureviewedit.h \
    ../View/structureViewBuilder/structurevieweditsubfeild.h \
    ../View/structureViewBuilder/structurevieweditsubfeildequation.h \
    ../View/structureViewBuilder/structurevieweditsubfeildtable.h \
    ../View/structureViewBuilder/structurevieweditsubfeildtablecolumn.h \
    ../View/structureViewBuilder/structurevieweditsubfeildtablecolumnquery.h \
    ../View/structureViewBuilder/structurevieweditsubfeildtablecolumnqueryui.h \
    ../View/structureViewBuilder/structureviewgroupsui.h \
    ../View/structureViewBuilder/structureviewseditui.h \
    ../View/createeditui.h \
    ../View/feildui.h \
    ../View/indexui.h \
    ../View/loginui.h \
    ../View/maindisplay.h \
    ../View/mainform.h \
    ../View/pageui.h \
    ../View/subfeildui.h \
    ../View/viewgroup.h \
    ../View/viewgroups.h \
    ../Model/database3.h \
    ../Model/merplyreporttablemodel.h \
    ../Model/model.h \
    ../Model/couchbaselibmanager.h \
    ../View/commonUI/qtooltipper.h \
    ../Model/prsistance.h \
    ../Model/user.h \
    ../View/structureViewBuilder/structureviewrefrence.h \
    ../View/structureViewBuilder/structureviewrefrencesubfield.h

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





macx: LIBS += -L$$PWD/../../../../../../../usr/local/Cellar/libcouchbase/2.7.1/lib/ -lcouchbase

INCLUDEPATH += $$PWD/../../../../../../../usr/local/Cellar/libcouchbase/2.7.1/include
DEPENDPATH += $$PWD/../../../../../../../usr/local/Cellar/libcouchbase/2.7.1/include

DISTFILES += \
    ../Model/Model.pri \
    ../Controller/Controller.pri \
    ../View/View.pri

