#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T22:01:16
#
#-------------------------------------------------

QT       += core gui webkit
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = osmc-browser
TEMPLATE = app


SOURCES += main.cpp\
        browser.cpp \
    logger.cpp

HEADERS  += browser.h \
    logger.h

FORMS    += browser.ui
