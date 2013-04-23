

HEADERS += slide_list_model.h \
           slide_data.h

SOURCES += pointy_tests.cpp \
      ../src/slide_list_model.cpp \
      ../src/slide_data.cpp

INCLUDEPATH += ../src/

#DEPENDPATH += . ../src/


QT += testlib

CONFIG += debug
