TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS =  src \
           tests \
           tests/qml_tests

QMAKE_CXXFLAGS += -std=c++11

