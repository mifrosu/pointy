#include "slide_data.h"
#include "slide_list_model.h"
#include <qdebug.h>
#include <qtextstream.h>
#include <iostream>
#include <qstring.h>

#include <qguiapplication.h>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>


void helpMessage(const char* execName, QTextStream& qout);
void printRaw(const pointy::SlideListModel& showModel, QTextStream& qout);

int main(int argc, char* argv[])
{
    QTextStream qout(stdout, QIODevice::WriteOnly);
    bool rawPrint(false);

    if (argc > 1) {
        for (int i=1; i < argc; ++i) {
            if (QString(argv[i])=="-h" ||
                    QString(argv[i]) == "--help") {
                helpMessage(argv[0], qout);
                return 0;
            }
            if (QString(argv[i]) == "-r" ||
                    QString(argv[i]) == "--raw") {
                rawPrint = true;
            }
        }

        //QGuiApplication app();

        std::cout << "Reading: " << argv[argc - 1] <<std::endl;
        QString fileName = argv[argc - 1];
        pointy::SlideListModel showModel;
        showModel.readSlideFile(fileName);
        if (rawPrint) {
            printRaw(showModel, qout);
            return 0;
        }
        QQuickView view;
        view.setResizeMode(QQuickView::SizeRootObjectToView);
        QQmlContext* context = view.rootContext();
        context->setContextProperty("slideShow", &showModel);

//        view.setSource(QUrl("qrc:view.qml"));
//        view.show();

//        return app.exec();

    }
    else {
        helpMessage(argv[0], qout);
        return 0;
    }
    return 0;
}


void helpMessage(const char* execName, QTextStream& qout)
{
    QString msg = QString("\nUsage:"
                          "%1 [arguments] [file]\n"
                          "\nArguments:\n"
                          "\t-h, --help\t Print this message, then exit\n"
                          "\t-r, --raw\t Write processed slide text to stdout,"
                          " then exit"
            ).arg(execName);
    qout << msg << endl << endl;
}

void printRaw(const pointy::SlideListModel &showModel, QTextStream &qout)
{
    QStringList slideData = showModel.getRawSlideData();
    QStringList::const_iterator iter = slideData.begin();
    QStringList::const_iterator endIter = slideData.end();
    //int slideNumber(0);
    while (iter != endIter) {
        qout <<  iter->toUtf8() << endl;
        ++iter;
      //  ++slideNumber;
    }
}
