/****************************************************************************
** Meta object code from reading C++ file 'QlfTUB.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QlfTUB.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QlfTUB.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QlfTUB[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,    8,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,    7,    7,    7, 0x0a,
      62,   52,    7,    7, 0x0a,
      71,    7,    7,    7, 0x2a,
      77,    7,    7,    7, 0x0a,
      84,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QlfTUB[] = {
    "QlfTUB\0\0code,msTime\0dataReady(int,int)\0"
    "resetTimer()\0msTimeout\0run(int)\0run()\0"
    "stop()\0setRange(Range)\0"
};

void QlfTUB::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QlfTUB *_t = static_cast<QlfTUB *>(_o);
        switch (_id) {
        case 0: _t->dataReady((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->resetTimer(); break;
        case 2: _t->run((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->run(); break;
        case 4: _t->stop(); break;
        case 5: _t->setRange((*reinterpret_cast< Range(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QlfTUB::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QlfTUB::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QlfTUB,
      qt_meta_data_QlfTUB, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QlfTUB::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QlfTUB::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QlfTUB::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QlfTUB))
        return static_cast<void*>(const_cast< QlfTUB*>(this));
    return QObject::qt_metacast(_clname);
}

int QlfTUB::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QlfTUB::dataReady(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
