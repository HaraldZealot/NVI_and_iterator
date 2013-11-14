TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -pedantic-errors

SOURCES += \
    main.cpp \
    tree.cpp \
    simpletree.cpp \
    set.cpp

HEADERS += \
    tree.h \
    simpletree.h \
    set.h

