#ifndef SLIDE_DATA_H
#define SLIDE_DATA_H

#include <QtCore/qstring.h>
#include <QtCore/qlist.h>

namespace pointy {

class SlideData
{
public:
    SlideData();

    QString stage_color;		// transition tint
    QString font;
    QString notes_font;
    QString notes_font_size;
    QString text_color;
    QString text_align;
    QString shading_color; 		// text rectangle bground color
    qreal shading_opacity;
    qreal duration;
    QString command;
    QString transition;
    int camera_frame_rate;
    QString background_scale;
    QString position;
    bool use_markup;
    QString slide_text;
    QString slide_media;
};


}

#endif // SLIDE_DATA_H
