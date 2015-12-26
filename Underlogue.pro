TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/ulAssetManager.cpp \
    src/ulScriptReader.cpp \
    #parser/test.cc \
    parser/ul-driver.cc \

INCLUDEPATH +=./include ./parser
HEADERS += \
    include/ulAssetManager.h \
    include/ulScriptReader.h \
    parser/dialogue.h \
    parser/ul-driver.hh

DISTFILES += \
    parser/parser.mk \
    parser/ul-scanner.ll \
    parser/ul-parser.yy \
    parser/Makefile

LIBS += parser/ul-parser.o parser/ul-scanner.o
