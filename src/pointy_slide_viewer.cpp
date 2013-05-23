#include "pointy_slide_viewer.h"

PointySlideViewer::PointySlideViewer(QWindow* parent) :
    QtQuick2ApplicationViewer(parent)
{

}

PointySlideViewer::~PointySlideViewer()
{
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

//void PointySlideViewer::keyPressEvent(QKeyEvent *event){
//    switch(event->key()) {
//    case Qt::Key_F:
//

//        break;
//    }
//}
