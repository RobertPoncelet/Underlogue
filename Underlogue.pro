TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/ulAssetManager.cpp \
    src/ulScriptReader.cpp \
    parser/test.cc \
    parser/ul-driver.cc \
    parser/lex.yy.c

INCLUDEPATH +=./include ./parser
HEADERS += \
    include/ulAssetManager.h \
    include/ulScriptReader.h \
    parser/dialogue.h \
    parser/ul-driver.hh

DISTFILES += \
    parser/parser.mk \
    parser/scriptTest.txt \
    parser/scriptTestBranch.txt \
    parser/scriptTestSimple.txt \
    parser/tempNotes.txt \
    parser/ul-parser.yy \
    parser/ul-scanner.ll \
    parser/Makefile
