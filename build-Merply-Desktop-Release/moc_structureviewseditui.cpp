/****************************************************************************
** Meta object code from reading C++ file 'structureviewseditui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/structureViewBuilder/structureviewseditui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'structureviewseditui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StructureViewsEditUI_t {
    QByteArrayData data[14];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StructureViewsEditUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StructureViewsEditUI_t qt_meta_stringdata_StructureViewsEditUI = {
    {
QT_MOC_LITERAL(0, 0, 20), // "StructureViewsEditUI"
QT_MOC_LITERAL(1, 21, 7), // "changed"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 12), // "styleChanged"
QT_MOC_LITERAL(4, 43, 12), // "updateLayout"
QT_MOC_LITERAL(5, 56, 18), // "controller_Clicked"
QT_MOC_LITERAL(6, 75, 3), // "btn"
QT_MOC_LITERAL(7, 79, 6), // "layout"
QT_MOC_LITERAL(8, 86, 16), // "joinGroupChanged"
QT_MOC_LITERAL(9, 103, 4), // "join"
QT_MOC_LITERAL(10, 108, 14), // "groupActivated"
QT_MOC_LITERAL(11, 123, 11), // "removeField"
QT_MOC_LITERAL(12, 135, 8), // "QWidget*"
QT_MOC_LITERAL(13, 144, 5) // "field"

    },
    "StructureViewsEditUI\0changed\0\0"
    "styleChanged\0updateLayout\0controller_Clicked\0"
    "btn\0layout\0joinGroupChanged\0join\0"
    "groupActivated\0removeField\0QWidget*\0"
    "field"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StructureViewsEditUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   57,    2, 0x0a /* Public */,
       3,    1,   60,    2, 0x0a /* Public */,
       8,    1,   63,    2, 0x0a /* Public */,
      10,    1,   66,    2, 0x0a /* Public */,
      11,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void StructureViewsEditUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StructureViewsEditUI *_t = static_cast<StructureViewsEditUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->styleChanged(); break;
        case 2: _t->updateLayout(); break;
        case 3: _t->controller_Clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->styleChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->joinGroupChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->groupActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->removeField((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
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
            typedef void (StructureViewsEditUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StructureViewsEditUI::changed)) {
                *result = 0;
            }
        }
        {
            typedef void (StructureViewsEditUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StructureViewsEditUI::styleChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (StructureViewsEditUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StructureViewsEditUI::updateLayout)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject StructureViewsEditUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StructureViewsEditUI.data,
      qt_meta_data_StructureViewsEditUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StructureViewsEditUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StructureViewsEditUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StructureViewsEditUI.stringdata0))
        return static_cast<void*>(const_cast< StructureViewsEditUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int StructureViewsEditUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void StructureViewsEditUI::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void StructureViewsEditUI::styleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void StructureViewsEditUI::updateLayout()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
