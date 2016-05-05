/****************************************************************************
** Meta object code from reading C++ file 'permissionfieldui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/permissionsUI/permissionfieldui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'permissionfieldui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PermissionFieldUI_t {
    QByteArrayData data[14];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PermissionFieldUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PermissionFieldUI_t qt_meta_stringdata_PermissionFieldUI = {
    {
QT_MOC_LITERAL(0, 0, 17), // "PermissionFieldUI"
QT_MOC_LITERAL(1, 18, 10), // "showSpcfic"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "field"
QT_MOC_LITERAL(4, 36, 17), // "allowGroupPressed"
QT_MOC_LITERAL(5, 54, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 71, 4), // "item"
QT_MOC_LITERAL(7, 76, 6), // "column"
QT_MOC_LITERAL(8, 83, 16), // "denyGroupPressed"
QT_MOC_LITERAL(9, 100, 9), // "addDenied"
QT_MOC_LITERAL(10, 110, 10), // "addAllowed"
QT_MOC_LITERAL(11, 121, 9), // "loadUsers"
QT_MOC_LITERAL(12, 131, 20), // "QList<QJsonDocument>"
QT_MOC_LITERAL(13, 152, 5) // "users"

    },
    "PermissionFieldUI\0showSpcfic\0\0field\0"
    "allowGroupPressed\0QTreeWidgetItem*\0"
    "item\0column\0denyGroupPressed\0addDenied\0"
    "addAllowed\0loadUsers\0QList<QJsonDocument>\0"
    "users"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PermissionFieldUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       4,    2,   47,    2, 0x0a /* Public */,
       8,    2,   52,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,
      10,    0,   58,    2, 0x0a /* Public */,
      11,    1,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void PermissionFieldUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PermissionFieldUI *_t = static_cast<PermissionFieldUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showSpcfic((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->allowGroupPressed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->denyGroupPressed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->addDenied(); break;
        case 4: _t->addAllowed(); break;
        case 5: _t->loadUsers((*reinterpret_cast< QList<QJsonDocument>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QJsonDocument> >(); break;
            }
            break;
        }
    }
}

const QMetaObject PermissionFieldUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PermissionFieldUI.data,
      qt_meta_data_PermissionFieldUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PermissionFieldUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PermissionFieldUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PermissionFieldUI.stringdata0))
        return static_cast<void*>(const_cast< PermissionFieldUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int PermissionFieldUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
