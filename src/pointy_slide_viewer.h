#ifndef POINTY_SLIDE_VIEWER_H
#define POINTY_SLIDE_VIEWER_H

#include "qtquick2applicationviewer.h"
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

signals:
    void fileIsChanged();

private:
    QFileInfo currentFileInfo;
    QDateTime fileLastModified;

    //void keyPressEvent(QKeyEvent *event);


};

#endif // POINTY_SLIDE_VIEWER_H
