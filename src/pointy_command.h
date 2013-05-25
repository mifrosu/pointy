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


#ifndef POINTY_COMMAND_H
#define POINTY_COMMAND_H

#include <qprocess.h>
#include <qsharedpointer.h>
#include <qobject.h>

namespace pointy {



class PointyCommand: public QObject
{
    Q_OBJECT
public:
    PointyCommand();

public slots:
    void runCommand(const QString& command);
    //void commandFinished(int exitCode, QProcess::ExitStatus exitStatus);


private:
    QSharedPointer<QProcess> process;
};

}  // namespace pointy
#endif // POINTY_COMMAND_H
