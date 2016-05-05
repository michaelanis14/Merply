/****************************************************************************
** Meta object code from reading C++ file 'structureviewedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/structureViewBuilder/structureviewedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'structureviewedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StructureViewEdit_t {
    QByteArrayData data[11];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StructureViewEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StructureViewEdit_t qt_meta_stringdata_StructureViewEdit = {
    {
QT_MOC_LITERAL(0, 0, 17), // "StructureViewEdit"
QT_MOC_LITERAL(1, 18, 7), // "changed"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "updatePreview"
QT_MOC_LITERAL(4, 41, 8), // "oldStrct"
QT_MOC_LITERAL(5, 50, 18), // "controller_Clicked"
QT_MOC_LITERAL(6, 69, 3), // "btn"
QT_MOC_LITERAL(7, 73, 8), // "addField"
QT_MOC_LITERAL(8, 82, 11), // "removeField"
QT_MOC_LITERAL(9, 94, 8), // "QWidget*"
QT_MOC_LITERAL(10, 103, 5) // "field"

    },
    "StructureViewEdit\0changed\0\0updatePreview\0"
    "oldStrct\0controller_Clicked\0btn\0"
    "addField\0removeField\0QWidget*\0field"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StructureViewEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x0a /* Public */,
       3,    0,   48,    2, 0x2a /* Public | MethodCloned */,
       5,    1,   49,    2, 0x0a /* Public */,
       7,    0,   52,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void StructureViewEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StructureViewEdit *_t = static_cast<StructureViewEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->updatePreview((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updatePreview(); break;
        case 3: _t->controller_Clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->addField(); break;
        case 5: _t->removeField((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StructureViewEdit::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StructureViewEdit::changed)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject StructureViewEdit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StructureViewEdit.data,
      qt_meta_data_StructureViewEdit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StructureViewEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StructureViewEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StructureViewEdit.stringdata0))
        return static_cast<void*>(const_cast< StructureViewEdit*>(this));
    return QWidget::qt_metacast(_clname);
}

int StructureViewEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void StructureViewEdit::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
