#-------------------------------------------------
#
# Project created by QtCreator 2018-07-28T09:59:15
#
#-------------------------------------------------

QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JackGB
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Rendering/Data/vertex.cpp \
    Rendering/glwindow.cpp \
    UI/mainwindow.cpp \
    CPU/cpu.cpp \
    ROM/rom.cpp \
    Memory/memory.cpp \
    gameboy.cpp \
    CPU/interrupts.cpp \
    Input/input.cpp \
    Rendering/display.cpp \
    CPU/instructions.cpp

HEADERS += \
    Rendering/Data/vertex.h \
    Rendering/glwindow.h \
    UI/mainwindow.h \
    CPU/cpu.h \
    CPU/registers.h \
    Memory/bootrom.h \
    ROM/rom.h \
    Memory/memory.h \
    gameboy.h \
    CPU/instructions.h \
    CPU/interrupts.h \
    Input/input.h \
    Rendering/display.h \
    CPU/flags.h

FORMS +=
    UI/mainwindow.ui

DISTFILES += \
    Rendering/Shaders/first.frag.glsl \
    Rendering/Shaders/first.vert.glsl
