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
