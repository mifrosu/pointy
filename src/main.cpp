/*  
 *  This file is part of Pointy.
 *
 *  Copyright (C) 2013 Michael O'Sullivan 
 *
 *  Pointy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Pointy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Pointy.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Written by: Michael O'Sullivan
 */

#include "pointy_slide_viewer.h"
#include "slide_data.h"
#include "slide_list_model.h"
#include "pointy_command.h"
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
#include "qtquick2applicationviewer.h"
#include "qdir.h"
#include "qqmlpropertymap.h"
#include <QKeyEvent>
#include <qfileinfo.h>
#include <qdatetime.h>


void helpMessage(const char* execName, QTextStream& qout);
void printRaw(const pointy::SlideListModel& showModel, QTextStream& qout);

int main(int argc, char* argv[])
{

    QTextStream qout(stdout, QIODevice::WriteOnly);
    bool rawPrint(false);
    bool setFullScreen(false);

    if (argc > 1) {
        for (int i=1; i < argc; ++i) {
            if (QString(argv[i])=="-h" ||
                    QString(argv[i]) == "--help") {
                helpMessage(argv[0], qout);
                return 0;
            }
            else if (QString(argv[i]) == "-r" ||
                    QString(argv[i]) == "--raw") {
                rawPrint = true;
            }
            else if (QString(argv[i]) == "-f" ||
                     QString(argv[i]) == "--fullscreen") {
                setFullScreen = true;
            }
        }



        QGuiApplication app(argc, argv);

        std::cout << "Reading: " << argv[argc - 1] <<std::endl;
        QString fileName = argv[argc - 1];
        pointy::SlideListModel showModel;
        showModel.readSlideFile(fileName);
        if (rawPrint) {
            printRaw(showModel, qout);
            return 0;
        }        

        //QtQuick2ApplicationViewer view;
        PointySlideViewer view;

        // monitor slide source file for updates
        view.setFileMonitor(fileName);
        view.setPosition(0,0);

        //view.setResizeMode(QQuickView::SizeRootObjectToView);
        QQmlContext* context = view.rootContext();
        context->setContextProperty("slideShow", &showModel);

        // To allow Qt Quick component access to the application's
        // working directory
        QString workingDir = QDir::currentPath();

        // Build the path, add it as a context property, and expose
        // it to QML
        QSharedPointer<QQmlPropertyMap> currentPath =
                QSharedPointer<QQmlPropertyMap>(new QQmlPropertyMap);


        currentPath->insert("currentDir", QVariant(QString("file://" +
                                                           workingDir + "/")));
        context->setContextProperty("currentPath", &(*currentPath));

        view.setMainQmlFile("src/qml/SlideView.qml");
        //view.showFullScreen();
        view.showExpanded();

        if (setFullScreen == true) {
            view.toggleFullScreen();
        }

        QObject *rootObject = qobject_cast<QObject*>(view.rootObject());
        QObject::connect(rootObject, SIGNAL(toggleScreenMode()),
                         &view, SLOT(toggleFullScreen()));
        QObject::connect(rootObject,SIGNAL(quitPointy()),
                         &view, SLOT(close()));
        QObject::connect(rootObject, SIGNAL(checkFileInfo()),
                         &view, SLOT(checkFileChanged()));
        QObject::connect(&view, SIGNAL(fileIsChanged()),
                         &showModel, SLOT(reloadSlides()));
        QObject::connect(rootObject,SIGNAL(sendCommand(QString)),
                         &view, SLOT(runCommand(QString)));




        return app.exec();



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
                          "\nArguments:\n\n"
                          "\t-f, --fullscreen\t\t"
                          "Start presentation in fullscreen mode\n"
                          "\t-h, --help\t\t\tPrint this message, then exit\n"
                          "\t-r, --raw\t\t\t"
                          "Write raw slides to stdout,"
                          " then exit"
                          "\n\nPresentation Controls:\n\n"
                          "\tSpacebar\t\t\tNext Slide\n"
                          "\tBackspace\t\t\tPrevious Slide\n"
                          "\tLeft/Right Cursor keys\t\tSkip to "
                          "previous/next slide\n"
                          "\tg\t\t\t\tToggle Grid Window\n"
                          "\tn\t\t\t\tToggle Notes Window\n"
                          "\tReturn\t\t\t\tPlay Media\n"
                          "\t<, >\t\t\t\tSeek backwards/forwards\n"
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

