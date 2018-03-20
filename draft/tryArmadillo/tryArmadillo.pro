TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

#QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += $$PWD/../../3rdParty/armadillo-code/include \
               ../tests
LIBS += $$PWD/../../3rdParty/armadillo-code/examples/lib_win64/lapack_win64_MT.lib
LIBS += $$PWD/../../3rdParty/armadillo-code/examples/lib_win64/blas_win64_MT.lib

SOURCES += main.cpp

HEADERS += \
    typelib.h \
    description.h \
    traitwr.h \
    wrarma.h \
    mathutil.h \
    ../tests/test.h
