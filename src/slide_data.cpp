#include "slide_data.h"
#include <qregexp.h>
#include <qcolor.h>

namespace pointy {

SlideData::SlideData():
    stageColor("black"), font("Sans 60px"), notesFont("Sans"),
    notesFontSize("20px"), textColor("white"), textAlign("left"),
    shadingColor("black"), shadingOpacity(0.66), duration(30),
    command(), transition("fade"), cameraFrameRate(0), backgroundScale("fill"),
    position("center"), useMarkup(true), slideText(), slideMedia(),
    backgroundColor("white"), notesText(), slideNumber(0)
{}

void SlideData::slideSettingAssign(const QString &lhs_in,
                                   const QString &rhs_in)
{
    QString lhs((lhs_in.toLower()).trimmed());
    QString rhs(rhs_in.trimmed());

    if (lhs == "stage-color") {
        this->stageColor = rhs;
    }
    else if (lhs == "font") {
        this->font = rhs;
    }
    else if (lhs == "notes-font") {
        this->notesFont = rhs;
    }
    else if (lhs == "notes-font-size") {
        this->notesFontSize = rhs;
    }
    else if (lhs == "text-color") {
        this->textColor = rhs;
    }
    else if (lhs == "text-align") {
        this->textAlign = rhs;
    }
    else if (lhs == "shading-color") {
        this->shadingColor = rhs;
    }
    else if (lhs == "shading-opacity") {
        bool ok;
        qreal temp = rhs.toFloat(&ok);
        if (!ok) {
            return;
        }
        else {
        this->shadingOpacity = temp;
        }
    }
    else if (lhs == "duration") {
        bool ok;
        qreal temp = rhs.toFloat(&ok);
        if (!ok) {
            return;
        }
        else {
            this->duration = temp;
        }
    }
    else if (lhs == "transition") {
        this->transition = rhs;
    }
    else if (lhs == "camera-framerate") {
        bool ok;
        int temp = rhs.toInt(&ok);
        if (!ok) {
            return;
        }
        else {
            this->cameraFrameRate = temp;
        }
    }

}

void SlideData::slideSettingAssign(const QString& setting)
{
    QString input = setting.trimmed();

    if (input.indexOf(".") != -1) {
        this->slideMedia = input;
    }
    else {
        QString lowerInput = input.toLower();
        if (lowerInput.indexOf("markup") != -1) {
            if (lowerInput == "no-markup") {
                this->useMarkup = false;
            }
            else {
                this->useMarkup = true;

            }
        }
        else if ((QRegExp("fill|fit|stretch|unscaled")
                  .exactMatch(lowerInput))) {
            this->backgroundScale = lowerInput;
        }
        else if (isValidPosition(lowerInput)) {
            this->position = lowerInput;
        }
        else if (QColor::isValidColor(lowerInput)) {
                this->backgroundColor = lowerInput;
        }
    }

}

bool SlideData::isValidPosition(const QString& testString)
{
    return(QRegExp("(top-left|top|top-right|"
                   "left|center|right|"
                   "bottom-left|bottom|bottom-right)")
            .exactMatch(testString));
}


}   // namespace pointy
