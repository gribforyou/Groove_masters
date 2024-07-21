QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    difficult_list_widget.cpp \
    level_widget.cpp \
    main.cpp \
    mainwindow.cpp \
    menu_widget.cpp \
    scores_widget.cpp \
    settings_widget.cpp \
    song_info.cpp \
    song_info_widget.cpp \
    song_list_widget.cpp \
    song_select_menu.cpp \
    start_widget.cpp \
    note.cpp

HEADERS += \
    difficult_list_widget.h \
    level_widget.h \
    mainwindow.h \
    menu_widget.h \
    scores_widget.h \
    settings_widget.h \
    song_info.h \
    song_info_widget.h \
    song_list_widget.h \
    song_select_menu.h \
    start_widget.h \
    note.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
