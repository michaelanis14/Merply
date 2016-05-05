/****************************************************************************
** Meta object code from reading C++ file 'structurevieweditsubfeildtablecolumn.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/structureViewBuilder/structurevieweditsubfeildtablecolumn.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'structurevieweditsubfeildtablecolumn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StructureVieweditSubFeildTableColumn_t {
    QByteArrayData data[13];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StructureVieweditSubFeildTableColumn_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StructureVieweditSubFeildTableColumn_t qt_meta_stringdata_StructureVieweditSubFeildTableColumn = {
    {
QT_MOC_LITERAL(0, 0, 36), // "StructureVieweditSubFeildTabl..."
QT_MOC_LITERAL(1, 37, 13), // "columnChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 12), // "updateFields"
QT_MOC_LITERAL(4, 65, 5), // "value"
QT_MOC_LITERAL(5, 71, 12), // "updateSelect"
QT_MOC_LITERAL(6, 84, 6), // "entity"
QT_MOC_LITERAL(7, 91, 16), // "updateSelectData"
QT_MOC_LITERAL(8, 108, 14), // "QList<QString>"
QT_MOC_LITERAL(9, 123, 6), // "fields"
QT_MOC_LITERAL(10, 130, 10), // "selectData"
QT_MOC_LITERAL(11, 141, 20), // "QList<QJsonDocument>"
QT_MOC_LITERAL(12, 162, 5) // "items"

    },
    "StructureVieweditSubFeildTableColumn\0"
    "columnChanged\0\0updateFields\0value\0"
    "updateSelect\0entity\0updateSelectData\0"
    "QList<QString>\0fields\0selectData\0"
    "QList<QJsonDocument>\0items"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StructureVieweditSubFeildTableColumn[] = {

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

void StructureVieweditSubFeildTableColumn::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StructureVieweditSubFeildTableColumn *_t = static_cast<StructureVieweditSubFeildTableColumn *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->columnChanged(); break;
        case 1: _t->updateFields((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->updateSelect((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->updateSelectData((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 4: _t->selectData((*reinterpret_cast< QList<QJsonDocument>(*)>(_a[1]))); break;
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
            typedef void (StructureVieweditSubFeildTableColumn::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StructureVieweditSubFeildTableColumn::columnChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject StructureVieweditSubFeildTableColumn::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StructureVieweditSubFeildTableColumn.data,
      qt_meta_data_StructureVieweditSubFeildTableColumn,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StructureVieweditSubFeildTableColumn::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StructureVieweditSubFeildTableColumn::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StructureVieweditSubFeildTableColumn.stringdata0))
        return static_cast<void*>(const_cast< StructureVieweditSubFeildTableColumn*>(this));
    return QWidget::qt_metacast(_clname);
}

int StructureVieweditSubFeildTableColumn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void StructureVieweditSubFeildTableColumn::columnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
