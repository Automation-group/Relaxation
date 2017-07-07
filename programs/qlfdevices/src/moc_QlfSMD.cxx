/****************************************************************************
** Meta object code from reading C++ file 'QlfSMD.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QlfSMD.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QlfSMD.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QlfSMD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      18,    7,    7,    7, 0x05,
      29,    7,    7,    7, 0x05,
      40,    7,    7,    7, 0x05,
      61,    7,    7,    7, 0x05,
      80,    7,    7,    7, 0x05,
     101,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     130,  120,    7,    7, 0x0a,
     139,    7,    7,    7, 0x2a,
     145,    7,    7,    7, 0x0a,
     152,    7,    7,    7, 0x0a,
     161,    7,    7,    7, 0x0a,
     182,  171,    7,    7, 0x0a,
     218,  208,    7,    7, 0x0a,
     255,  242,    7,    7, 0x0a,
     285,  275,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QlfSMD[] = {
    "QlfSMD\0\0runDone()\0overload()\0overheat()\0"
    "forwardTrailerDown()\0forwardTrailerUp()\0"
    "reverseTrailerDown()\0reverseTrailerUp()\0"
    "stepCount\0run(int)\0run()\0stop()\0"
    "enable()\0disable()\0conformity\0"
    "setConformity(Conformity)\0direction\0"
    "setDirection(Direction)\0counterValue\0"
    "setStepCounter(int)\0frequency\0"
    "setFrequency(double)\0"
};

void QlfSMD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QlfSMD *_t = static_cast<QlfSMD *>(_o);
        switch (_id) {
        case 0: _t->runDone(); break;
        case 1: _t->overload(); break;
        case 2: _t->overheat(); break;
        case 3: _t->forwardTrailerDown(); break;
        case 4: _t->forwardTrailerUp(); break;
        case 5: _t->reverseTrailerDown(); break;
        case 6: _t->reverseTrailerUp(); break;
        case 7: _t->run((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->run(); break;
        case 9: _t->stop(); break;
        case 10: _t->enable(); break;
        case 11: _t->disable(); break;
        case 12: _t->setConformity((*reinterpret_cast< Conformity(*)>(_a[1]))); break;
        case 13: _t->setDirection((*reinterpret_cast< Direction(*)>(_a[1]))); break;
        case 14: _t->setStepCounter((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->setFrequency((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QlfSMD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QlfSMD::staticMetaObject = {
    { &QlfSPDevice::staticMetaObject, qt_meta_stringdata_QlfSMD,
      qt_meta_data_QlfSMD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QlfSMD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QlfSMD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QlfSMD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QlfSMD))
        return static_cast<void*>(const_cast< QlfSMD*>(this));
    return QlfSPDevice::qt_metacast(_clname);
}

int QlfSMD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QlfSPDevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void QlfSMD::runDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QlfSMD::overload()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QlfSMD::overheat()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QlfSMD::forwardTrailerDown()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QlfSMD::forwardTrailerUp()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QlfSMD::reverseTrailerDown()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void QlfSMD::reverseTrailerUp()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
