#include "pointy_slide_viewer.h"
#include <qdebug.h>

PointySlideViewer::PointySlideViewer(QWindow* parent) :
    QtQuick2ApplicationViewer(parent)
{

}

PointySlideViewer::~PointySlideViewer()
{
}

void PointySlideViewer::setFileMonitor(const QString &fileName)
{
    currentFileInfo = fileName;
    fileLastModified = currentFileInfo.lastModified();
}

void PointySlideViewer::checkFileChanged()
{
    currentFileInfo.refresh();
    QDateTime newFileCheck = currentFileInfo.lastModified();
    if (newFileCheck != fileLastModified)
    {
        emit fileIsChanged();
        fileLastModified = newFileCheck;
    }
    else {
        return;
    }
}

void PointySlideViewer::toggleFullScreen()
{
    if (this->windowState()!=Qt::WindowFullScreen) {
        this->setWindowState(Qt::WindowFullScreen);
    }
    else {
        this->setWindowState(Qt::WindowNoState);
    }
}

void PointySlideViewer::runCommand(const QString &command) {
    qDebug() << "Running:" << command;
    pointyCommand.runCommand(command);
}

//void PointySlideViewer::keyPressEvent(QKeyEvent *event){
//    switch(event->key()) {
//    case Qt::Key_F:
//

//        break;
//    }
//}
