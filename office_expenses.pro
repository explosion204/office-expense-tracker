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
    service/computeunit.cpp \
    service/controlunit.cpp \
    service/database.cpp \
    service/diagram.cpp

HEADERS += \
    ../../../Python/include/Python-ast.h \
    ../../../Python/include/Python.h \
    ../../../Python/include/abstract.h \
    ../../../Python/include/asdl.h \
    ../../../Python/include/ast.h \
    ../../../Python/include/bitset.h \
    ../../../Python/include/bltinmodule.h \
    ../../../Python/include/boolobject.h \
    ../../../Python/include/bytearrayobject.h \
    ../../../Python/include/bytes_methods.h \
    ../../../Python/include/bytesobject.h \
    ../../../Python/include/cellobject.h \
    ../../../Python/include/ceval.h \
    ../../../Python/include/classobject.h \
    ../../../Python/include/code.h \
    ../../../Python/include/codecs.h \
    ../../../Python/include/compile.h \
    ../../../Python/include/complexobject.h \
    ../../../Python/include/context.h \
    ../../../Python/include/cpython/abstract.h \
    ../../../Python/include/cpython/dictobject.h \
    ../../../Python/include/cpython/fileobject.h \
    ../../../Python/include/cpython/initconfig.h \
    ../../../Python/include/cpython/interpreteridobject.h \
    ../../../Python/include/cpython/object.h \
    ../../../Python/include/cpython/objimpl.h \
    ../../../Python/include/cpython/pyerrors.h \
    ../../../Python/include/cpython/pylifecycle.h \
    ../../../Python/include/cpython/pymem.h \
    ../../../Python/include/cpython/pystate.h \
    ../../../Python/include/cpython/sysmodule.h \
    ../../../Python/include/cpython/traceback.h \
    ../../../Python/include/cpython/tupleobject.h \
    ../../../Python/include/cpython/unicodeobject.h \
    ../../../Python/include/datetime.h \
    ../../../Python/include/descrobject.h \
    ../../../Python/include/dictobject.h \
    ../../../Python/include/dtoa.h \
    ../../../Python/include/dynamic_annotations.h \
    ../../../Python/include/enumobject.h \
    ../../../Python/include/errcode.h \
    ../../../Python/include/eval.h \
    ../../../Python/include/fileobject.h \
    ../../../Python/include/fileutils.h \
    ../../../Python/include/floatobject.h \
    ../../../Python/include/frameobject.h \
    ../../../Python/include/funcobject.h \
    ../../../Python/include/genobject.h \
    ../../../Python/include/graminit.h \
    ../../../Python/include/grammar.h \
    ../../../Python/include/import.h \
    ../../../Python/include/internal/pycore_accu.h \
    ../../../Python/include/internal/pycore_atomic.h \
    ../../../Python/include/internal/pycore_ceval.h \
    ../../../Python/include/internal/pycore_code.h \
    ../../../Python/include/internal/pycore_condvar.h \
    ../../../Python/include/internal/pycore_context.h \
    ../../../Python/include/internal/pycore_fileutils.h \
    ../../../Python/include/internal/pycore_getopt.h \
    ../../../Python/include/internal/pycore_gil.h \
    ../../../Python/include/internal/pycore_hamt.h \
    ../../../Python/include/internal/pycore_initconfig.h \
    ../../../Python/include/internal/pycore_object.h \
    ../../../Python/include/internal/pycore_pathconfig.h \
    ../../../Python/include/internal/pycore_pyerrors.h \
    ../../../Python/include/internal/pycore_pyhash.h \
    ../../../Python/include/internal/pycore_pylifecycle.h \
    ../../../Python/include/internal/pycore_pymem.h \
    ../../../Python/include/internal/pycore_pystate.h \
    ../../../Python/include/internal/pycore_traceback.h \
    ../../../Python/include/internal/pycore_tupleobject.h \
    ../../../Python/include/internal/pycore_warnings.h \
    ../../../Python/include/interpreteridobject.h \
    ../../../Python/include/intrcheck.h \
    ../../../Python/include/iterobject.h \
    ../../../Python/include/listobject.h \
    ../../../Python/include/longintrepr.h \
    ../../../Python/include/longobject.h \
    ../../../Python/include/marshal.h \
    ../../../Python/include/memoryobject.h \
    ../../../Python/include/methodobject.h \
    ../../../Python/include/modsupport.h \
    ../../../Python/include/moduleobject.h \
    ../../../Python/include/namespaceobject.h \
    ../../../Python/include/node.h \
    ../../../Python/include/object.h \
    ../../../Python/include/objimpl.h \
    ../../../Python/include/odictobject.h \
    ../../../Python/include/opcode.h \
    ../../../Python/include/osdefs.h \
    ../../../Python/include/osmodule.h \
    ../../../Python/include/parsetok.h \
    ../../../Python/include/patchlevel.h \
    ../../../Python/include/picklebufobject.h \
    ../../../Python/include/py_curses.h \
    ../../../Python/include/pyarena.h \
    ../../../Python/include/pycapsule.h \
    ../../../Python/include/pyconfig.h \
    ../../../Python/include/pyctype.h \
    ../../../Python/include/pydebug.h \
    ../../../Python/include/pydtrace.h \
    ../../../Python/include/pyerrors.h \
    ../../../Python/include/pyexpat.h \
    ../../../Python/include/pyfpe.h \
    ../../../Python/include/pyhash.h \
    ../../../Python/include/pylifecycle.h \
    ../../../Python/include/pymacconfig.h \
    ../../../Python/include/pymacro.h \
    ../../../Python/include/pymath.h \
    ../../../Python/include/pymem.h \
    ../../../Python/include/pyport.h \
    ../../../Python/include/pystate.h \
    ../../../Python/include/pystrcmp.h \
    ../../../Python/include/pystrhex.h \
    ../../../Python/include/pystrtod.h \
    ../../../Python/include/pythonrun.h \
    ../../../Python/include/pythread.h \
    ../../../Python/include/pytime.h \
    ../../../Python/include/rangeobject.h \
    ../../../Python/include/setobject.h \
    ../../../Python/include/sliceobject.h \
    ../../../Python/include/structmember.h \
    ../../../Python/include/structseq.h \
    ../../../Python/include/symtable.h \
    ../../../Python/include/sysmodule.h \
    ../../../Python/include/token.h \
    ../../../Python/include/traceback.h \
    ../../../Python/include/tracemalloc.h \
    ../../../Python/include/tupleobject.h \
    ../../../Python/include/typeslots.h \
    ../../../Python/include/ucnhash.h \
    ../../../Python/include/unicodeobject.h \
    ../../../Python/include/warnings.h \
    ../../../Python/include/weakrefobject.h \
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
    service/computeunit.h \
    service/controlunit.h \
    service/database.h \
    service/diagram.h

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

unix|win32: LIBS += -L$$PWD/../../../Python/libs/ -lpython38

INCLUDEPATH += $$PWD/../../../Python/libs
DEPENDPATH += $$PWD/../../../Python/libs

unix|win32: LIBS += -L$$PWD/../../../Python/libs/ -lpython3

INCLUDEPATH += $$PWD/../../../Python/libs
DEPENDPATH += $$PWD/../../../Python/libs

unix|win32: LIBS += -L$$PWD/../../../Python/libs/ -l_tkinter

INCLUDEPATH += $$PWD/../../../Python/libs
DEPENDPATH += $$PWD/../../../Python/libs
