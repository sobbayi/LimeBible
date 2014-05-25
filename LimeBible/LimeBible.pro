#-------------------------------------------------
#
# Project created by QtCreator 2011-06-04T12:03:13
#
#-------------------------------------------------

QT       += core gui network


TARGET = LimeBible
TEMPLATE = app
VERSION = 1.3.0


SOURCES += main.cpp\
    mainwnd.cpp \
    aboutdlg.cpp \
    updatedlg.cpp \
    datahelper.cpp \
    sqlite3.c \
    searchdlg.cpp

HEADERS  += mainwnd.h \
    aboutdlg.h \
    updatedlg.h \
    datahelper.h \
    sqlite3.h \
    globals.h \
    searchdlg.h

win32 {
     HEADERS += version.h
 }

DEFINES += LimeRes



win32:RC_FILE +=  \
    win.rc

unix {
    QMAKE_LFLAGS += -Wl,-rpath=\\\$\$ORIGIN
    QMAKE_LFLAGS += -Wl,-rpath=\\\$\$ORIGIN/libs
    QMAKE_RPATH=
}
