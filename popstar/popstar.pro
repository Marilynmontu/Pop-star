#-------------------------------------------------
#
# Project created by QtCreator 2016-04-19T14:52:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = popstar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    field.cpp

HEADERS  += mainwindow.h \
    field.h

FORMS    += mainwindow.ui

# 启用 C++ 11 支持（以使用随机数引擎）
QMAKE_CXXFLAGS += -std=c++11
