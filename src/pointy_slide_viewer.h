#ifndef POINTY_SLIDE_VIEWER_H
#define POINTY_SLIDE_VIEWER_H

#include "qtquick2applicationviewer.h"
#include <QKeyEvent>

class PointySlideViewer: public QtQuick2ApplicationViewer
{
    Q_OBJECT
public:
    explicit PointySlideViewer(QWindow* parent = 0);
    virtual ~PointySlideViewer();

public slots:
    void toggleFullScreen();

    //void keyPressEvent(QKeyEvent *event);


};

#endif // POINTY_SLIDE_VIEWER_H
