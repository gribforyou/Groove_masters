/****************************************************************************
** Meta object code from reading C++ file 'menu_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../GrooveMasters/menu_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menu_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Menu_Widget_t {
    QByteArrayData data[8];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Menu_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Menu_Widget_t qt_meta_stringdata_Menu_Widget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Menu_Widget"
QT_MOC_LITERAL(1, 12, 11), // "back_signal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "settings_signal"
QT_MOC_LITERAL(4, 41, 11), // "exit_signal"
QT_MOC_LITERAL(5, 53, 9), // "back_slot"
QT_MOC_LITERAL(6, 63, 13), // "settings_slot"
QT_MOC_LITERAL(7, 77, 9) // "exit_slot"

    },
    "Menu_Widget\0back_signal\0\0settings_signal\0"
    "exit_signal\0back_slot\0settings_slot\0"
    "exit_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Menu_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Menu_Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Menu_Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->back_signal(); break;
        case 1: _t->settings_signal(); break;
        case 2: _t->exit_signal(); break;
        case 3: _t->back_slot(); break;
        case 4: _t->settings_slot(); break;
        case 5: _t->exit_slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Menu_Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Menu_Widget::back_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Menu_Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Menu_Widget::settings_signal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Menu_Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Menu_Widget::exit_signal)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Menu_Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Menu_Widget.data,
    qt_meta_data_Menu_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Menu_Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Menu_Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Menu_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Menu_Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Menu_Widget::back_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Menu_Widget::settings_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Menu_Widget::exit_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
