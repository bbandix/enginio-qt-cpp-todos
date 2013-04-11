QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../enginio-qt/enginio_client/release/ -lenginioclient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../enginio-qt/enginio_client/debug/ -lenginioclientd
else:unix: LIBS += -L$$OUT_PWD/../enginio-qt/enginio_client/ -lenginioclient

macx {
    enginioClientLib.path = Contents/MacOS/Libs
    enginioClientLib.files = $$OUT_PWD/../enginio-qt/enginio_client/libenginioclient.1.0.0.dylib
    QMAKE_BUNDLE_DATA += enginioClientLib
    QMAKE_POST_LINK += install_name_tool -change libenginioclient.1.dylib @executable_path/Libs/libenginioclient.1.0.0.dylib $(TARGET)
}

INCLUDEPATH += $$PWD/../enginio-qt/enginio_client
DEPENDPATH += $$PWD/../enginio-qt/enginio_client
