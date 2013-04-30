include($$PWD/../enginio-qt/enginio.pri)
QT += gui widgets

TARGET = cpp_todos
TEMPLATE = app

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    todoitemdelegate.cpp

HEADERS += \
    mainwindow.h \
    todoitemdelegate.h \
    applicationconfig.h
