/****************************************************************************
** Meta object code from reading C++ file 'timelineui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/commonUI/timelineui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timelineui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_timelineUI_t {
    QByteArrayData data[4];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_timelineUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_timelineUI_t qt_meta_stringdata_timelineUI = {
    {
QT_MOC_LITERAL(0, 0, 10), // "timelineUI"
QT_MOC_LITERAL(1, 11, 14), // "btnLoadPressed"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13) // "btnRunPressed"

    },
    "timelineUI\0btnLoadPressed\0\0btnRunPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_timelineUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void timelineUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        timelineUI *_t = static_cast<timelineUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->btnLoadPressed(); break;
        case 1: _t->btnRunPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (timelineUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&timelineUI::btnLoadPressed)) {
                *result = 0;
            }
        }
        {
            typedef void (timelineUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&timelineUI::btnRunPressed)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject timelineUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_timelineUI.data,
      qt_meta_data_timelineUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *timelineUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *timelineUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_timelineUI.stringdata0))
        return static_cast<void*>(const_cast< timelineUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int timelineUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void timelineUI::btnLoadPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void timelineUI::btnRunPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
