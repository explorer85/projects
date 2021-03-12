QT = core testlib
TEMPLATE = app

CONFIG += c++11 c++14
CONFIG += console testcase no_testcase_installs

HEADERS += \
    ../../jsonparser.h

SOURCES += \
    ../../jsonparser.cpp \
    jsonparsertest.cpp



