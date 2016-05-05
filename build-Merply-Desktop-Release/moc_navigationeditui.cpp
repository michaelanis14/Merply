/****************************************************************************
** Meta object code from reading C++ file 'navigationeditui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/commonUI/NavigationUI/navigationeditui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'navigationeditui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NavigationEditUI_t {
    QByteArrayData data[15];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NavigationEditUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NavigationEditUI_t qt_meta_stringdata_NavigationEditUI = {
    {
QT_MOC_LITERAL(0, 0, 16), // "NavigationEditUI"
QT_MOC_LITERAL(1, 17, 13), // "subNavPressed"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 4), // "view"
QT_MOC_LITERAL(4, 37, 14), // "mainNavPressed"
QT_MOC_LITERAL(5, 52, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 69, 4), // "item"
QT_MOC_LITERAL(7, 74, 6), // "column"
QT_MOC_LITERAL(8, 81, 14), // "mainNavChanged"
QT_MOC_LITERAL(9, 96, 11), // "btn_Clicked"
QT_MOC_LITERAL(10, 108, 3), // "btn"
QT_MOC_LITERAL(11, 112, 23), // "btn_ClickedDataReturned"
QT_MOC_LITERAL(12, 136, 8), // "document"
QT_MOC_LITERAL(13, 145, 27), // "editControllerCancelPressed"
QT_MOC_LITERAL(14, 173, 25) // "editControllerSavePressed"

    },
    "NavigationEditUI\0subNavPressed\0\0view\0"
    "mainNavPressed\0QTreeWidgetItem*\0item\0"
    "column\0mainNavChanged\0btn_Clicked\0btn\0"
    "btn_ClickedDataReturned\0document\0"
    "editControllerCancelPressed\0"
    "editControllerSavePressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NavigationEditUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   57,    2, 0x0a /* Public */,
       8,    2,   62,    2, 0x0a /* Public */,
       1,    2,   67,    2, 0x0a /* Public */,
       9,    1,   72,    2, 0x0a /* Public */,
      11,    1,   75,    2, 0x0a /* Public */,
      13,    0,   78,    2, 0x0a /* Public */,
      14,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QJsonDocument,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NavigationEditUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NavigationEditUI *_t = static_cast<NavigationEditUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->subNavPressed((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 1: _t->mainNavPressed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->mainNavChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->subNavPressed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->btn_Clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->btn_ClickedDataReturned((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 6: _t->editControllerCancelPressed(); break;
        case 7: _t->editControllerSavePressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NavigationEditUI::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NavigationEditUI::subNavPressed)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject NavigationEditUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NavigationEditUI.data,
      qt_meta_data_NavigationEditUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NavigationEditUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavigationEditUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NavigationEditUI.stringdata0))
        return static_cast<void*>(const_cast< NavigationEditUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int NavigationEditUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void NavigationEditUI::subNavPressed(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
