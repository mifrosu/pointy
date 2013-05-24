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
