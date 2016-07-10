QT += core
QT -= gui

CONFIG += c++11

TARGET = GNC
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gnc_converter.cpp

HEADERS += \
    gnc_converter.h
