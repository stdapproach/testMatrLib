TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../3rdParty/armadillo-code/include
LIBS += $$PWD/../../3rdParty/armadillo-code/examples/lib_win64/lapack_win64_MT.lib

SOURCES += main.cpp
