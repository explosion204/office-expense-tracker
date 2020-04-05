#-------------------------------------------------
#
# Project created by QtCreator 2020-02-19T09:37:09
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = office_expenses
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_STATICPLAGIN

QTPLUGIN += sqlitecipher

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    data/aggregator.cpp \
    data/department.cpp \
    data/expense.cpp \
    gui/department_item.cpp \
    gui/department_widget.cpp \
    gui/expense_item.cpp \
    gui/expense_widget.cpp \
    gui/loginwindow.cpp \
    gui/mainwindow.cpp \
    main.cpp \
    permissions/account.cpp \
    permissions/administrator.cpp \
    permissions/manager.cpp \
    permissions/moderator.cpp \
    service/animation.cpp \
    service/controlunit.cpp \
    service/database.cpp

HEADERS += \
    data/aggregator.h \
    data/datastatus.h \
    data/department.h \
    data/expense.h \
    data/snapshots.h \
    gui/department_item.h \
    gui/department_widget.h \
    gui/expense_item.h \
    gui/expense_widget.h \
    gui/loginwindow.h \
    gui/mainwindow.h \
    gui/widget_purpose.h \
    lib/picosha2.h \ \
    permissions/account.h \
    permissions/administrator.h \
    permissions/manager.h \
    permissions/moderator.h \
    permissions/permission.h \
    service/animation.h \
    service/controlunit.h \
    service/database.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/lib/ -llibssl

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix|win32: LIBS += -L$$PWD/lib/ -llibcrypto

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix|win32: LIBS += -L$$PWD/lib/ -lsqlitecipher

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES += \
    lib/libcrypto.lib \
    lib/libsqlitecipher.a \
    lib/libssl.lib \

FORMS += \
    gui/department_widget.ui \
    gui/expense_widget.ui \
    gui/loginwindow.ui \
    gui/mainwindow.ui
