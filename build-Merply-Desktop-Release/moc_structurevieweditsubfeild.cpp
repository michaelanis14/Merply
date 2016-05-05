/****************************************************************************
** Meta object code from reading C++ file 'structurevieweditsubfeild.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/structureViewBuilder/structurevieweditsubfeild.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'structurevieweditsubfeild.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StructureVieweditSubFeild_t {
    QByteArrayData data[13];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StructureVieweditSubFeild_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StructureVieweditSubFeild_t qt_meta_stringdata_StructureVieweditSubFeild = {
    {
QT_MOC_LITERAL(0, 0, 25), // "StructureVieweditSubFeild"
QT_MOC_LITERAL(1, 26, 7), // "changed"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "updateFields"
QT_MOC_LITERAL(4, 48, 4), // "type"
QT_MOC_LITERAL(5, 53, 12), // "updateSelect"
QT_MOC_LITERAL(6, 66, 5), // "title"
QT_MOC_LITERAL(7, 72, 16), // "updateSelectData"
QT_MOC_LITERAL(8, 89, 14), // "QList<QString>"
QT_MOC_LITERAL(9, 104, 6), // "fields"
QT_MOC_LITERAL(10, 111, 13), // "gotSourceData"
QT_MOC_LITERAL(11, 125, 20), // "QList<QJsonDocument>"
QT_MOC_LITERAL(12, 146, 5) // "items"

    },
    "StructureVieweditSubFeild\0changed\0\0"
    "updateFields\0type\0updateSelect\0title\0"
    "updateSelectData\0QList<QString>\0fields\0"
    "gotSourceData\0QList<QJsonDocument>\0"
    "items"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StructureVieweditSubFeild[] = {

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
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,
       7,    1,   46,    2, 0x0a /* Public */,
      10,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void StructureVieweditSubFeild::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StructureVieweditSubFeild *_t = static_cast<StructureVieweditSubFeild *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->updateFields((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->updateSelect((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->updateSelectData((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 4: _t->gotSourceData((*reinterpret_cast< QList<QJsonDocument>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        case 4:
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
            typedef void (StructureVieweditSubFeild::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StructureVieweditSubFeild::changed)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject StructureVieweditSubFeild::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StructureVieweditSubFeild.data,
      qt_meta_data_StructureVieweditSubFeild,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StructureVieweditSubFeild::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StructureVieweditSubFeild::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StructureVieweditSubFeild.stringdata0))
        return static_cast<void*>(const_cast< StructureVieweditSubFeild*>(this));
    return QWidget::qt_metacast(_clname);
}

int StructureVieweditSubFeild::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void StructureVieweditSubFeild::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
