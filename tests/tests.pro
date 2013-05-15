QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += . ../src/

#DEPENDPATH += . ../src/


HEADERS += \
          ../src/slide_list_model.h \
          ../src/slide_data.h \
    pointy_text_parse_tests.h \
    pointy_test_file_read.h \
    pointy_test_slide_setting.h

SOURCES += \
      ../src/slide_list_model.cpp \
      ../src/slide_data.cpp \
    main.cpp \
    pointy_text_parse_tests.cpp \
    pointy_test_file_read.cpp \
    pointy_test_slide_setting.cpp



QT += testlib

CONFIG += debug \
    warn_on qmltestcase

RESOURCES += \
    test_resources.qrc
