#-------------------------------------------------
#
# Project created by QtCreator 2013-11-09T16:08:55
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtWordreference
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wordreferenceclient.cpp \
    worddefinition.cpp \
    wordtranslation.cpp \
    translationentry.cpp \
    optionsdialog.cpp

HEADERS  += mainwindow.h \
    wordreferenceclient.h \
    worddefinition.h \
    wordtranslation.h \
    translationentry.h \
    optionsdialog.h

FORMS    += mainwindow.ui \
    optionsdialog.ui

RESOURCES += \
    icons.qrc

CONFIG(debug, debug|release) {
    DEFINES += DEBUG_MODE
}else {
    message("release mode")
}
