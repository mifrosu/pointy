QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += . ../src/

#DEPENDPATH += . ../src/


HEADERS += \
          ../src/slide_list_model.h \
          ../src/slide_data.h \
    pointy_text_parse_tests.h \
    pointy_test_file_read.h

SOURCES += \
      ../src/slide_list_model.cpp \
      ../src/slide_data.cpp \
    main.cpp \
    pointy_text_parse_tests.cpp \
    pointy_test_file_read.cpp



QT += testlib

CONFIG += debug

RESOURCES += \
    test_resources.qrc
