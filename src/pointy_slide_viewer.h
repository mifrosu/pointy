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


#ifndef POINTY_SLIDE_VIEWER_H
#define POINTY_SLIDE_VIEWER_H

#include "qtquick2applicationviewer.h"
#include "pointy_command.h"
#include <QKeyEvent>
#include <qdatetime.h>
#include <qfileinfo.h>

class PointySlideViewer: public QtQuick2ApplicationViewer
{
    Q_OBJECT
public:
    explicit PointySlideViewer(QWindow* parent = 0);
    virtual ~PointySlideViewer();
    void setFileMonitor(const QString& fileName);


public slots:
    void checkFileChanged();
    void toggleFullScreen();
    void runCommand(const QString& command);

signals:
    void fileIsChanged();

private:
    QFileInfo currentFileInfo;
    QDateTime fileLastModified;
    pointy::PointyCommand pointyCommand;

    //void keyPressEvent(QKeyEvent *event);


};

#endif // POINTY_SLIDE_VIEWER_H
