QT += quick

CONFIG += c++11 c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        jsonparser.cpp \
        main.cpp \
        parametersmodel.cpp

HEADERS += \
    jsonparser.h \
    parametersmodel.h

RESOURCES += qml.qrc

OTHER_FILES += \
data.json

message($$OUT_PWD)
target.files = $$OTHER_FILES
target.path = $$OUT_PWD
!isEmpty(target.path): INSTALLS += target




