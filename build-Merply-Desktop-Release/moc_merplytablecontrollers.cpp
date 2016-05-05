/****************************************************************************
** Meta object code from reading C++ file 'merplytablecontrollers.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/commonUI/merplytablecontrollers.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'merplytablecontrollers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_merplyTableControllers_t {
    QByteArrayData data[6];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_merplyTableControllers_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_merplyTableControllers_t qt_meta_stringdata_merplyTableControllers = {
    {
QT_MOC_LITERAL(0, 0, 22), // "merplyTableControllers"
QT_MOC_LITERAL(1, 23, 11), // "editClicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 13), // "deleteClicked"
QT_MOC_LITERAL(4, 50, 15), // "btn_editClicked"
QT_MOC_LITERAL(5, 66, 17) // "btn_deleteClicked"

    },
    "merplyTableControllers\0editClicked\0\0"
    "deleteClicked\0btn_editClicked\0"
    "btn_deleteClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_merplyTableControllers[] = {

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
       1,    1,   34,    2, 0x06 /* Public */,
       3,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   40,    2, 0x0a /* Public */,
       5,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void merplyTableControllers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        merplyTableControllers *_t = static_cast<merplyTableControllers *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->deleteClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->btn_editClicked(); break;
        case 3: _t->btn_deleteClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (merplyTableControllers::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&merplyTableControllers::editClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (merplyTableControllers::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&merplyTableControllers::deleteClicked)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject merplyTableControllers::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_merplyTableControllers.data,
      qt_meta_data_merplyTableControllers,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *merplyTableControllers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *merplyTableControllers::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_merplyTableControllers.stringdata0))
        return static_cast<void*>(const_cast< merplyTableControllers*>(this));
    return QWidget::qt_metacast(_clname);
}

int merplyTableControllers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void merplyTableControllers::editClicked(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void merplyTableControllers::deleteClicked(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
