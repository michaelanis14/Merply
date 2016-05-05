/****************************************************************************
** Meta object code from reading C++ file 'expandbutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/commonUI/expandbutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'expandbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ExpandButton_t {
    QByteArrayData data[7];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExpandButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExpandButton_t qt_meta_stringdata_ExpandButton = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ExpandButton"
QT_MOC_LITERAL(1, 13, 4), // "hide"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "show"
QT_MOC_LITERAL(4, 24, 16), // "btnArroW_Clicked"
QT_MOC_LITERAL(5, 41, 17), // "updateDescription"
QT_MOC_LITERAL(6, 59, 4) // "text"

    },
    "ExpandButton\0hide\0\0show\0btnArroW_Clicked\0"
    "updateDescription\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExpandButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   36,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void ExpandButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ExpandButton *_t = static_cast<ExpandButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hide(); break;
        case 1: _t->show(); break;
        case 2: _t->btnArroW_Clicked(); break;
        case 3: _t->updateDescription((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ExpandButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ExpandButton::hide)) {
                *result = 0;
            }
        }
        {
            typedef void (ExpandButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ExpandButton::show)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ExpandButton::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ExpandButton.data,
      qt_meta_data_ExpandButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ExpandButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExpandButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ExpandButton.stringdata0))
        return static_cast<void*>(const_cast< ExpandButton*>(this));
    return QWidget::qt_metacast(_clname);
}

int ExpandButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ExpandButton::hide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ExpandButton::show()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
