/****************************************************************************
** Meta object code from reading C++ file 'subfeildui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/subfeildui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'subfeildui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SubFieldUI_t {
    QByteArrayData data[8];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SubFieldUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SubFieldUI_t qt_meta_stringdata_SubFieldUI = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SubFieldUI"
QT_MOC_LITERAL(1, 11, 16), // "indexedFillEvent"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "completion"
QT_MOC_LITERAL(4, 40, 11), // "linkPressed"
QT_MOC_LITERAL(5, 52, 12), // "refrenceData"
QT_MOC_LITERAL(6, 65, 20), // "QList<QJsonDocument>"
QT_MOC_LITERAL(7, 86, 5) // "items"

    },
    "SubFieldUI\0indexedFillEvent\0\0completion\0"
    "linkPressed\0refrenceData\0QList<QJsonDocument>\0"
    "items"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SubFieldUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    0,   32,    2, 0x0a /* Public */,
       5,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void SubFieldUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SubFieldUI *_t = static_cast<SubFieldUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->indexedFillEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->linkPressed(); break;
        case 2: _t->refrenceData((*reinterpret_cast< QList<QJsonDocument>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QJsonDocument> >(); break;
            }
            break;
        }
    }
}

const QMetaObject SubFieldUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SubFieldUI.data,
      qt_meta_data_SubFieldUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SubFieldUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SubFieldUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SubFieldUI.stringdata0))
        return static_cast<void*>(const_cast< SubFieldUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int SubFieldUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
