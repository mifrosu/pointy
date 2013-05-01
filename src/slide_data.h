#ifndef SLIDE_DATA_H
#define SLIDE_DATA_H

#include <QtCore/qstring.h>
#include <QtCore/qlist.h>

namespace pointy {

class SlideData
{
public:
    SlideData();

    QString stageColor;		// transition tint
    QString font;
    QString notesFont;
    QString notesFontSize;
    QString textColor;
    QString textAlign;
    QString shadingColor; 		// text rectangle bground color
    qreal shadingOpacity;
    qreal duration;
    QString command;
    QString transition;
    int cameraFrameRate;
    QString backgroundScale;
    QString position;
    bool useMarkup;
    QString slideText;
    QString slideMedia;
};


}

#endif // SLIDE_DATA_H
