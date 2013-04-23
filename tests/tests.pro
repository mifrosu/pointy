

HEADERS += slide_list_model.h \
           slide_data.h \
    pointy_text_parse_tests.h

SOURCES += \
      ../src/slide_list_model.cpp \
      ../src/slide_data.cpp \
    main.cpp \
    pointy_text_parse_tests.cpp

INCLUDEPATH += ../src/

#DEPENDPATH += . ../src/


QT += testlib

CONFIG += debug

RESOURCES += \
    test_resources.qrc
