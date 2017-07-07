/****************************************************************************
** Meta object code from reading C++ file 'MainDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      32,   11,   11,   11, 0x08,
      53,   11,   11,   11, 0x08,
      80,   11,   11,   11, 0x08,
     108,   11,   11,   11, 0x08,
     133,   11,   11,   11, 0x08,
     159,   11,   11,   11, 0x08,
     186,   11,   11,   11, 0x08,
     214,   11,   11,   11, 0x08,
     232,   11,   11,   11, 0x08,
     252,   11,   11,   11, 0x08,
     272,   11,   11,   11, 0x08,
     294,   11,   11,   11, 0x08,
     318,   11,   11,   11, 0x08,
     341,   11,   11,   11, 0x08,
     366,   11,   11,   11, 0x08,
     381,  379,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainDialog[] = {
    "MainDialog\0\0on_pbOpen_clicked()\0"
    "on_pbClose_clicked()\0on_pbEnableMotor_clicked()\0"
    "on_pbDisableMotor_clicked()\0"
    "on_pbReadSpeed_clicked()\0"
    "on_pbWriteSpeed_clicked()\0"
    "on_pbReadCounter_clicked()\0"
    "on_pbWriteCounter_clicked()\0"
    "on_tbUp_clicked()\0on_tbDown_clicked()\0"
    "on_tbStop_clicked()\0on_tbMoveUp_pressed()\0"
    "on_tbMoveDown_pressed()\0on_tbMoveUp_released()\0"
    "on_tbMoveDown_released()\0readAlarms()\0"
    "i\0on_cbInvertion_stateChanged(int)\0"
};

void MainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainDialog *_t = static_cast<MainDialog *>(_o);
        switch (_id) {
        case 0: _t->on_pbOpen_clicked(); break;
        case 1: _t->on_pbClose_clicked(); break;
        case 2: _t->on_pbEnableMotor_clicked(); break;
        case 3: _t->on_pbDisableMotor_clicked(); break;
        case 4: _t->on_pbReadSpeed_clicked(); break;
        case 5: _t->on_pbWriteSpeed_clicked(); break;
        case 6: _t->on_pbReadCounter_clicked(); break;
        case 7: _t->on_pbWriteCounter_clicked(); break;
        case 8: _t->on_tbUp_clicked(); break;
        case 9: _t->on_tbDown_clicked(); break;
        case 10: _t->on_tbStop_clicked(); break;
        case 11: _t->on_tbMoveUp_pressed(); break;
        case 12: _t->on_tbMoveDown_pressed(); break;
        case 13: _t->on_tbMoveUp_released(); break;
        case 14: _t->on_tbMoveDown_released(); break;
        case 15: _t->readAlarms(); break;
        case 16: _t->on_cbInvertion_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MainDialog,
      qt_meta_data_MainDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainDialog))
        return static_cast<void*>(const_cast< MainDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
