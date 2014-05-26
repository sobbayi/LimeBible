#-------------------------------------------------
#
# Project created by QtCreator 2011-09-16T10:57:54
#
#-------------------------------------------------

QT       += gui

TARGET = LimeRes
TEMPLATE = lib

DEFINES += LIMERES_LIBRARY

SOURCES += limeres.cpp

HEADERS += limeres.h\
        LimeRes_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE68190EE
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = LimeRes.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
