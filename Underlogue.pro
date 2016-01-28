TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QT += core
QT -= gui

SOURCES += \
    src/main.cpp \
    src/ulAssetManager.cpp \
    src/ulScriptReader.cpp \
    #parser/test.cc \
    parser/ul-driver.cc \
    src/ulDialogueBox.cpp \
    src/ulApplication.cpp \
    src/ulDialogueOption.cpp

INCLUDEPATH +=./include ./parser
HEADERS += \
    include/ulAssetManager.h \
    include/ulScriptReader.h \
    parser/dialogue.h \
    parser/ul-driver.hh \
    include/ulDialogueBox.h \
    include/ulApplication.h \
    include/ulLabel.h \
    include/ulDialogueOption.h

DISTFILES += \
    parser/parser.mk \
    parser/ul-scanner.ll \
    parser/ul-parser.yy \
    parser/Makefile

QMAKE_LFLAGS += -static

LIBS += parser/ul-parser.o parser/ul-scanner.o -lncurses++ -lform -lmenu -lpanel -lncurses -lutil \
    -lstdc++

OBJECTS_DIR = ./obj
