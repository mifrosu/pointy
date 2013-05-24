#include "pointy_command.h"
#include <qtextstream.h>

namespace pointy {

PointyCommand::PointyCommand()
{
    process = QSharedPointer<QProcess>(new QProcess);
}

void PointyCommand::runCommand(const QString &command)
{
    bool isSuccess = process->startDetached(command);
    if (!isSuccess) {
        QTextStream qout(stdout, QIODevice::WriteOnly);
        qout << "Command: " << command << " failed.";
    }


}


} // namespace pointy
