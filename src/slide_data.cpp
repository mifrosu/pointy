#include "slide_data.h"
#include <qregexp.h>
#include <qcolor.h>
#include <qfont.h>
#include <qfontinfo.h>
#include <QMessageLogger>
#include <qdebug.h>

namespace pointy {

SlideData::SlideData():
    stageColor("black"), font("Sans"), fontSize(60), fontSizeUnit("px"),
    notesFont("Sans"),
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
        setFont(rhs);
    }
    else if (lhs == "notes-font") {
        this->notesFont = rhs;
    }
    else if (lhs == "notes-font-size") {
        this->notesFontSize = rhs;
    }
    else if (lhs == "text-color") {
        if (QColor::isValidColor(rhs)) {
            this->textColor = rhs;
        }

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

void SlideData::setFont(const QString &fontString)
{
    QString testFont = fontString.toLower().trimmed();
    if ((QRegExp("(\\w+ \\d+ ?p(x|t))")).exactMatch(testFont))
        // 1+ alphanumeric chars followed by a space "\\w+ "
        // 1+ decimal digits followed by optional space "\\d ?"
        // either px or pt "p(x|t)"
    {
        int splitIndex = testFont.indexOf(QRegExp(" \\d+ ?[Pp]([Xx]|[Tt])"));
        QString possibleFont = (testFont.left(splitIndex)).trimmed();
        this->font = possibleFont;

        int splitUnitIndex = (testFont.mid(splitIndex)).
                indexOf(QRegExp("p(x|t)"));
        QStringList fontSettings;
        fontSettings.append((testFont.mid(splitIndex,
                                           splitUnitIndex)).trimmed());
        fontSettings.append(((testFont.mid(splitIndex)).
                             mid(splitUnitIndex)).trimmed());
        bool ok;
        qreal tempSize = fontSettings[0].toFloat(&ok);
        if (ok) {
            this->fontSize = tempSize;
        }
        if (fontSettings[1].toLower() == "pt") {
            this->fontSizeUnit = "pt";
        }
        else {
            this->fontSizeUnit = "px";
        }
    }
}


}   // namespace pointy
