/****************************************************************************
** Meta object code from reading C++ file 'navigationui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/commonUI/NavigationUI/navigationui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'navigationui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_navigationUI_t {
    QByteArrayData data[12];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_navigationUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_navigationUI_t qt_meta_stringdata_navigationUI = {
    {
QT_MOC_LITERAL(0, 0, 12), // "navigationUI"
QT_MOC_LITERAL(1, 13, 13), // "subNavPressed"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "view"
QT_MOC_LITERAL(4, 33, 14), // "mainNavPressed"
QT_MOC_LITERAL(5, 48, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 65, 4), // "item"
QT_MOC_LITERAL(7, 70, 6), // "column"
QT_MOC_LITERAL(8, 77, 11), // "btn_Clicked"
QT_MOC_LITERAL(9, 89, 3), // "btn"
QT_MOC_LITERAL(10, 93, 23), // "btn_ClickedDataReturned"
QT_MOC_LITERAL(11, 117, 8) // "document"

    },
    "navigationUI\0subNavPressed\0\0view\0"
    "mainNavPressed\0QTreeWidgetItem*\0item\0"
    "column\0btn_Clicked\0btn\0btn_ClickedDataReturned\0"
    "document"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_navigationUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   42,    2, 0x0a /* Public */,
       1,    2,   47,    2, 0x0a /* Public */,
       8,    1,   52,    2, 0x0a /* Public */,
      10,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QJsonDocument,   11,

       0        // eod
};

void navigationUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        navigationUI *_t = static_cast<navigationUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->subNavPressed((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 1: _t->mainNavPressed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->subNavPressed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->btn_Clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->btn_ClickedDataReturned((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (navigationUI::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&navigationUI::subNavPressed)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject navigationUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_navigationUI.data,
      qt_meta_data_navigationUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *navigationUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *navigationUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_navigationUI.stringdata0))
        return static_cast<void*>(const_cast< navigationUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int navigationUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void navigationUI::subNavPressed(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
