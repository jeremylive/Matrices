#-------------------------------------------------
#
# Project created by QtCreator 2017-06-04T10:45:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Matrix
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


SOURCES += main.cpp \
    screen.cpp \
    list_display.cpp \
    file_manager.cpp \
    file_thread.cpp \
    operator.cpp \
    w_sumador.cpp \
    w_multiplicador.cpp \
    v_display.cpp \
    w_writer.cpp \
    file_thread_constructor.cpp \
    v_matix_display.cpp \
    t_sumador.cpp \
    t_r_suma.cpp \
    t_r_multiplicador.cpp \
    t_multiplicador.cpp \
    t_transpuesta.cpp \
    t_mult_escalar.cpp \
    t_r_mul_es.cpp \
    t_verificar.cpp

HEADERS  += \
    screen.h \
    list_display.h \
    file_manager.h \
    file_thread.h \
    operator.h \
    w_sumador.h \
    w_multiplicador.h \
    v_display.h \
    w_writer.h \
    st_line.h \
    st_byte.h \
    file_thread_constructor.h \
    v_matix_display.h \
    t_sumador.h \
    t_r_suma.h \
    t_r_multiplicador.h \
    t_multiplicador.h \
    t_transpuesta.h \
    t_mult_escalar.h \
    t_r_mul_es.h \
    st_prop.h \
    t_verificar.h

FORMS    += mainwindow.ui

QMAKE_EXTRA_COMPILERS += nasm
NASMEXTRAFLAGS = -f elf64 -g -F dwarf
OTHER_FILES += $$NASM_SOURCES
nasm.output = ${QMAKE_FILE_BASE}.o
nasm.commands = nasm $$NASMEXTRAFLAGS -o ${QMAKE_FILE_BASE}.o ${QMAKE_FILE_NAME}
nasm.input = NASM_SOURCES

NASM_SOURCES += mul_es.asm

DISTFILES += \
    mul_es.asm



