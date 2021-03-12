QT = core testlib
TEMPLATE = app

CONFIG += c++11 c++14
CONFIG += console testcase no_testcase_installs

HEADERS += \
    ../../jsonparser.h

SOURCES += \
    ../../jsonparser.cpp \
    jsonparsertest.cpp


OTHER_FILES += \
data/empty.json \
data/keyvalue.json \
data/arrayofvalue.json

message($$OUT_PWD)
target.files = $$OTHER_FILES
target.path = $$OUT_PWD
!isEmpty(target.path): INSTALLS += target


