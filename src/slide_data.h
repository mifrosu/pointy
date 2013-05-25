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


#ifndef SLIDE_DATA_H
#define SLIDE_DATA_H

#include <QtCore/qstring.h>
#include <QtCore/qlist.h>
#include <qsharedpointer.h>

namespace pointy {

class SlideData
{
public:
    SlideData();

    QString stageColor;		// transition tint
    QString font;
    qreal fontSize;
    QString fontSizeUnit;
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
    int maxLineLength;
    QString slideMedia;
    QString backgroundColor;
    QString notesText;
    int slideNumber;

    void slideSettingAssign(const QString& lhs_in, const QString& rhs_in);
    void slideSettingAssign(const QString& setting);
    void setFont(const QString& fontString);

private:
    bool isValidPosition(const QString& testString);
};

}   // namespace pointy

#endif // SLIDE_DATA_H
