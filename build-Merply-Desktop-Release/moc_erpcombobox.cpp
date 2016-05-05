/****************************************************************************
** Meta object code from reading C++ file 'erpcombobox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/commonUI/erpcombobox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'erpcombobox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ERPComboBox_t {
    QByteArrayData data[8];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ERPComboBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ERPComboBox_t qt_meta_stringdata_ERPComboBox = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ERPComboBox"
QT_MOC_LITERAL(1, 12, 12), // "refreshModel"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "indexedFillEvent"
QT_MOC_LITERAL(4, 43, 10), // "completion"
QT_MOC_LITERAL(5, 54, 13), // "focusOutEvent"
QT_MOC_LITERAL(6, 68, 12), // "QFocusEvent*"
QT_MOC_LITERAL(7, 81, 1) // "e"

    },
    "ERPComboBox\0refreshModel\0\0indexedFillEvent\0"
    "completion\0focusOutEvent\0QFocusEvent*\0"
    "e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ERPComboBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   33,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void ERPComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ERPComboBox *_t = static_cast<ERPComboBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refreshModel(); break;
        case 1: _t->indexedFillEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->focusOutEvent((*reinterpret_cast< QFocusEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ERPComboBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ERPComboBox::refreshModel)) {
                *result = 0;
            }
        }
        {
            typedef void (ERPComboBox::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ERPComboBox::indexedFillEvent)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ERPComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_ERPComboBox.data,
      qt_meta_data_ERPComboBox,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ERPComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ERPComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ERPComboBox.stringdata0))
        return static_cast<void*>(const_cast< ERPComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int ERPComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ERPComboBox::refreshModel()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ERPComboBox::indexedFillEvent(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
