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
