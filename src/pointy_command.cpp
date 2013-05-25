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

#include "pointy_command.h"
#include <qtextstream.h>

namespace pointy {

PointyCommand::PointyCommand()
{
    process = QSharedPointer<QProcess>(new QProcess);
}

void PointyCommand::runCommand(const QString &command)
{
    if (command.startsWith("sudo ") || command.startsWith("rm ") ||
            command.startsWith("su ")) {
                QTextStream qout(stdout, QIODevice::WriteOnly);
                qout << "Command: " << command << " is not permitted.";
                return;
    }
    process->start(command);
//        bool isSuccess = process->startDetached(command);
//    if (!isSuccess) {
//        QTextStream qout(stdout, QIODevice::WriteOnly);
//        qout << "Command: " << command << " failed.";
//    }


}


} // namespace pointy
