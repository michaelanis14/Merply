/****************************************************************************
** Meta object code from reading C++ file 'merplytabelview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Merply/View/commonUI/merplytabelview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'merplytabelview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_merplyTabelView_t {
    QByteArrayData data[9];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_merplyTabelView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_merplyTabelView_t qt_meta_stringdata_merplyTabelView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "merplyTabelView"
QT_MOC_LITERAL(1, 16, 10), // "printTabel"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "editEntity"
QT_MOC_LITERAL(4, 39, 2), // "id"
QT_MOC_LITERAL(5, 42, 12), // "deleteEntity"
QT_MOC_LITERAL(6, 55, 16), // "updateHeaderData"
QT_MOC_LITERAL(7, 72, 14), // "QList<QString>"
QT_MOC_LITERAL(8, 87, 11) // "headerItems"

    },
    "merplyTabelView\0printTabel\0\0editEntity\0"
    "id\0deleteEntity\0updateHeaderData\0"
    "QList<QString>\0headerItems"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_merplyTabelView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       5,    1,   38,    2, 0x0a /* Public */,
       6,    1,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void merplyTabelView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        merplyTabelView *_t = static_cast<merplyTabelView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->printTabel(); break;
        case 1: _t->editEntity((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->deleteEntity((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateHeaderData((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
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
        }
    }
}

const QMetaObject merplyTabelView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_merplyTabelView.data,
      qt_meta_data_merplyTabelView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *merplyTabelView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *merplyTabelView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_merplyTabelView.stringdata0))
        return static_cast<void*>(const_cast< merplyTabelView*>(this));
    return QWidget::qt_metacast(_clname);
}

int merplyTabelView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
