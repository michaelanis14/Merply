/****************************************************************************
** Meta object code from reading C++ file 'navigationpageeditui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/commonUI/NavigationUI/navigationpageeditui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'navigationpageeditui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NavigationPageEditUI_t {
    QByteArrayData data[16];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NavigationPageEditUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NavigationPageEditUI_t qt_meta_stringdata_NavigationPageEditUI = {
    {
QT_MOC_LITERAL(0, 0, 20), // "NavigationPageEditUI"
QT_MOC_LITERAL(1, 21, 25), // "editControllerSavePressed"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 27), // "editControllerCancelPressed"
QT_MOC_LITERAL(4, 76, 11), // "btn_Clicked"
QT_MOC_LITERAL(5, 88, 3), // "btn"
QT_MOC_LITERAL(6, 92, 14), // "newCardToggled"
QT_MOC_LITERAL(7, 107, 5), // "state"
QT_MOC_LITERAL(8, 113, 11), // "cardToggled"
QT_MOC_LITERAL(9, 125, 11), // "pageToggled"
QT_MOC_LITERAL(10, 137, 11), // "getCardData"
QT_MOC_LITERAL(11, 149, 20), // "QList<QJsonDocument>"
QT_MOC_LITERAL(12, 170, 5), // "items"
QT_MOC_LITERAL(13, 176, 13), // "updatePreview"
QT_MOC_LITERAL(14, 190, 8), // "loadCard"
QT_MOC_LITERAL(15, 199, 8) // "document"

    },
    "NavigationPageEditUI\0editControllerSavePressed\0"
    "\0editControllerCancelPressed\0btn_Clicked\0"
    "btn\0newCardToggled\0state\0cardToggled\0"
    "pageToggled\0getCardData\0QList<QJsonDocument>\0"
    "items\0updatePreview\0loadCard\0document"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NavigationPageEditUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   61,    2, 0x0a /* Public */,
       6,    1,   64,    2, 0x0a /* Public */,
       8,    1,   67,    2, 0x0a /* Public */,
       9,    1,   70,    2, 0x0a /* Public */,
      10,    1,   73,    2, 0x0a /* Public */,
      13,    0,   76,    2, 0x0a /* Public */,
      14,    1,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonDocument,   15,

       0        // eod
};

void NavigationPageEditUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NavigationPageEditUI *_t = static_cast<NavigationPageEditUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editControllerSavePressed(); break;
        case 1: _t->editControllerCancelPressed(); break;
        case 2: _t->btn_Clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->newCardToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->cardToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->pageToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->getCardData((*reinterpret_cast< QList<QJsonDocument>(*)>(_a[1]))); break;
        case 7: _t->updatePreview(); break;
        case 8: _t->loadCard((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QJsonDocument> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NavigationPageEditUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NavigationPageEditUI::editControllerSavePressed)) {
                *result = 0;
            }
        }
        {
            typedef void (NavigationPageEditUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NavigationPageEditUI::editControllerCancelPressed)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject NavigationPageEditUI::staticMetaObject = {
    { &MainDisplay::staticMetaObject, qt_meta_stringdata_NavigationPageEditUI.data,
      qt_meta_data_NavigationPageEditUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NavigationPageEditUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavigationPageEditUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NavigationPageEditUI.stringdata0))
        return static_cast<void*>(const_cast< NavigationPageEditUI*>(this));
    return MainDisplay::qt_metacast(_clname);
}

int NavigationPageEditUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MainDisplay::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void NavigationPageEditUI::editControllerSavePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void NavigationPageEditUI::editControllerCancelPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
