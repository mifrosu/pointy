
SOURCES += \
    main.cpp \
    slide_list_model.cpp \
    slide_data.cpp


TEMPLATE = app

TARGET = ../pointy

HEADERS += \
    slide_data.h \
    slide_list_model.h

QT += core \
      qml quick

OTHER_FILES += \
    SlideView.qml

RESOURCES +=

folder_01.source = qml
folder_01.target =
DEPLOYMENTFOLDERS = folder_01

QML_IMPORT_PATH =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()




