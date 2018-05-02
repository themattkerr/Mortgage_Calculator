#-------------------------------------------------
#
# Project created by QtCreator 2017-10-16T22:13:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mortgage_Calculator
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


SOURCES += main.cpp\
        mainwindow.cpp \
    mortgagecalc.cpp \
    calculatemillratedialog.cpp \
    calculateothermonthlyexpensesdialog.cpp \
    aboutdialog.cpp \
    ../../Matts_Software/General_Library/mattcalculations.cpp \
    mortgagecalc.cpp \


HEADERS  += mainwindow.h \
    mortgagecalc.h \
    calculatemillratedialog.h \
    calculateothermonthlyexpensesdialog.h \
    aboutdialog.h \
    ../../Matts_Software/General_Library/mattcalculations.h


FORMS    += mainwindow.ui \
    calculatemillratedialog.ui \
    calculateothermonthlyexpensesdialog.ui \
    aboutdialog.ui

DISTFILES += \
    install.nsi \
    res.rc \
    Calculator.ico \
    mortgage1.ico \
    Mode Logo.png \
    Mode Logo.png \
    Mode Logo.bmp

RC_FILE = res.rc

#QMAKE_POST_LINK += windeployqt \"$$system_path($${OUT_PWD}/release/Mortgage_Calculator.exe)\" --dir \"$$system_path($${_PRO_FILE_PWD_}/Deploy)\"
#QMAKE_POST_LINK += && $$QMAKE_COPY \"$$system_path($${OUT_PWD}/release/Mortgage_Calculator.exe)\" \"$$system_path($${_PRO_FILE_PWD_}/Deploy/)\"
