#include "slide_list_model.h"
#include "slide_data.h"
#include <QtCore/QtCore>
#include <QMessageLogger>
#include <qregexp.h>
#include <qhash.h>
#include <qcolor.h>


namespace pointy {

SlideListModel::SlideListModel(QObject *parent) : QAbstractListModel(parent)
{
    customSlideSettings = QSharedPointer<SlideData>(new SlideData);

}


QVariant SlideListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();      // return a Null variant

    if (index.row() >= slideList.size() )
        return QVariant();

    const QSharedPointer<SlideData> currentSlide = slideList.at(index.row());
    switch (role) {
    case StageColorRole:
        return QVariant::fromValue(currentSlide->stageColor);
    case FontRole:
        return QVariant::fromValue(currentSlide->font);
    case NotesFontRole:
        return QVariant::fromValue(currentSlide->notesFont);
    case NotesFontSizeRole:
        return QVariant::fromValue(currentSlide->notesFontSize);
    case TextColorRole:
        return QVariant::fromValue(currentSlide->textColor);
    case TextAlignRole:
        return QVariant::fromValue(currentSlide->textAlign);
    case ShadingColorRole:
        return QVariant::fromValue(currentSlide->shadingColor);
    case ShadingOpacityRole:
        return QVariant::fromValue(currentSlide->shadingOpacity);
    case DurationRole:
        return QVariant::fromValue(currentSlide->duration);
    case CommandRole:
        return QVariant::fromValue(currentSlide->command);
    case TransitionRole:
        return QVariant::fromValue(currentSlide->transition);
    case CameraFrameRateRole:
        return QVariant::fromValue(currentSlide->cameraFrameRate);
    case BackgroundScaleRole:
        return QVariant::fromValue(currentSlide->backgroundScale);
    case PositionRole:
        return QVariant::fromValue(currentSlide->position);
    case UseMarkupRole:
        return QVariant::fromValue(currentSlide->useMarkup);
    case SlideTextRole:
        return QVariant::fromValue(currentSlide->slideText);
    case SlideMediaRole:
        return QVariant::fromValue(currentSlide->slideMedia);
    case BackgroundColorRole:
        return QVariant::fromValue(currentSlide->backgroundColor);
    case SlideNumberRole:
        return QVariant::fromValue(currentSlide->slideNumber);
    default:
        return QVariant();
    }
}

int SlideListModel::rowCount(const QModelIndex& parent) const
{
    return slideList.size();
}

QHash<int, QByteArray> SlideListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[StageColorRole] = "stageColor";
    roles[FontRole] = "font";
    roles[NotesFontRole] = "notesFont";
    roles[NotesFontSizeRole] = "notesFontSize";
    roles[TextColorRole] = "text";
    roles[TextAlignRole] = "textAlign";
    roles[ShadingColorRole] ="shadingColor";
    roles[ShadingOpacityRole] ="shadingOpacity";
    roles[DurationRole] ="duration";
    roles[CommandRole] ="command";
    roles[TransitionRole] ="transition";
    roles[CameraFrameRateRole] ="cameraRameRate";
    roles[BackgroundScaleRole] ="backgroundScale";
    roles[PositionRole] ="postition";
    roles[UseMarkupRole] ="useMarkup";
    roles[SlideTextRole] ="slideText";
    roles[SlideMediaRole] ="slideMedia";
    roles[BackgroundColorRole] ="backgroundColor";
    roles[SlideNumberRole] = "slideNumber";
    return roles;

}

void stripComments(QSharedPointer<QByteArray>& lineIn, const QString comment)
{
    if(!lineIn)
    {
        return;
    }
    int commentIndex = lineIn->indexOf(comment);
    if (commentIndex == -1) {
        // no comment in line
        return;
    }
    else if (commentIndex == 0) {
        // comment at start of line
        lineIn->clear();
    }
    else if (lineIn->at(commentIndex-1) == '\\'){
        // recursively check for escaped comments and actual comments
        QSharedPointer<QByteArray> remains =
                QSharedPointer<QByteArray>(new QByteArray);
        *remains = (lineIn->mid(commentIndex + 1));
        stripComments(remains);
        *lineIn = (lineIn->left(commentIndex + 1)).append(*remains);
    }
    else {
        *lineIn = (lineIn->left(commentIndex));
    }
}

void stripSquareBrackets(QSharedPointer<QByteArray>& lineIn,
                         QSharedPointer<QStringList>& store,
                         const int& lineCount)
{
    int numberStartBracket = lineIn->count("[");
    int numberEndBracket = lineIn->count("]");
    if (numberStartBracket != numberEndBracket)
    {
        qWarning("Line %d: incomplete brackets", lineCount);
        return;
    }
    int startBracket = lineIn->indexOf("[");
    if (startBracket < 0) {
        return;
    }

    int endBracket = lineIn->indexOf("]");
    if (endBracket < startBracket) {
        qWarning("Line %d: mismatched brackets", lineCount);
        return;
    }
    QSharedPointer<QByteArray> remains =
            QSharedPointer<QByteArray>(new QByteArray);
    *remains = (lineIn->mid(endBracket + 1));
    store->append(lineIn->mid(startBracket + 1, endBracket-(startBracket+1)));
    // recursive search for additional settings on the line
    stripSquareBrackets(remains,
                        store, lineCount);
}

void populateSlideSettings(QStringList &listIn,
                           QSharedPointer<SlideData> &currentSlide)
{
    if (listIn.isEmpty() || !currentSlide) {
        return;
    }

    QStringList::const_iterator iter;
    QStringList::const_iterator endIter = listIn.end();

    for (iter = listIn.begin(); iter != endIter; ++iter) {
        int equalsIndex = iter->indexOf("=");
        if (equalsIndex > 0) {
            currentSlide->slideSettingAssign(iter->left(equalsIndex),
                                             iter->mid(equalsIndex + 1));
            continue;
        }
        else {
            currentSlide->slideSettingAssign(*iter);
        }
    }

}

void SlideListModel::newSlideSetting()
{
    slideList.push_back(QSharedPointer<SlideData>(new SlideData));
}

void SlideListModel::newSlideSetting(const SlideData& customSlideSettings)
{
    slideList.push_back(QSharedPointer<SlideData>(
                            new SlideData(customSlideSettings)));
}


void SlideListModel::readSlideFile(const QString fileName)
{
    int lineCount = 0;      // for error reporting
    bool haveCustomSettings = false;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qFatal("Slide file can not be read");
    }

    QSharedPointer<QStringList> rawSettingsList = QSharedPointer<QStringList>
            (new QStringList);
    newSlideSetting();
    QSharedPointer<SlideData> currentSlideSettings = slideList.last();
    QSharedPointer<SlideData> customSlideSettings = slideList.first();
    QSharedPointer<QString> currentSlideText =
            QSharedPointer<QString>(new QString);

    while (!file.atEnd()) {
        ++lineCount;
        QSharedPointer<QByteArray> linePtr =
                QSharedPointer<QByteArray>(new QByteArray);
        *linePtr = file.readLine();
        stripComments(linePtr, "#");
        if (linePtr->startsWith("[") && haveCustomSettings == false) {
            stripSquareBrackets(linePtr, rawSettingsList, lineCount);
        }
        else if (linePtr->startsWith("--")) {
            if (haveCustomSettings == false) {
                // this is the first slide, so store header custom settings
                haveCustomSettings = true;
                populateSlideSettings(*rawSettingsList, customSlideSettings);
            }
            if (haveCustomSettings == true) {

                if (!(currentSlideText->isEmpty())) {
                    *currentSlideText = currentSlideText->trimmed();
                    currentSlideSettings->slideText = *currentSlideText;
                }

                newSlideSetting(*customSlideSettings);
                currentSlideSettings = slideList.last();
                rawSettingsList->clear();
                currentSlideText->clear();
            }

            if (linePtr->contains("[")) {
                stripSquareBrackets(linePtr,rawSettingsList, lineCount);
                populateSlideSettings(*rawSettingsList,
                                         currentSlideSettings);
            }
        }
        else {
            currentSlideText->append(*linePtr);
        }
    }
    if (!(currentSlideText->isEmpty())) {
        *currentSlideText = currentSlideText->trimmed();
        currentSlideSettings->slideText = *currentSlideText;
                // insert("slideText",*currentSlideText);
    }

}

QStringList SlideListModel::getRawSlideData() const
{
    QStringList rawData;
    QList<QSharedPointer<SlideData> >::const_iterator slideIter =
            slideList.begin();
    QList<QSharedPointer<SlideData> >::const_iterator endIter =
            slideList.end();
    while (slideIter != endIter) {
        rawData.append(("stageColor: " + (*slideIter)->stageColor));
        rawData.append(("font: " + (*slideIter)->font));
        rawData.append(("notesFont: " + (*slideIter)->notesFont));
        rawData.append(("notesFontSize: " + (*slideIter)->stageColor));
        rawData.append(("textColor: " + (*slideIter)->textColor));
        rawData.append(("textAlign: " + (*slideIter)->textAlign));
        rawData.append(("shadingColor: " + (*slideIter)->shadingColor));
        rawData.append(QString("shadingOpacity: %1").arg(
                           (*slideIter)->shadingOpacity));
        rawData.append(QString("duration: %1").arg(
                           (*slideIter)->duration));
        rawData.append(QString("command: %1").arg((*slideIter)->command));
        rawData.append(QString("transition: %1").arg(
                           (*slideIter)->transition));
        rawData.append(QString("cameraFrameRate: %1").arg(
                           (*slideIter)->cameraFrameRate));
        rawData.append(QString("backgroundScale: %1").arg(
                           (*slideIter)->backgroundScale));
        rawData.append(QString("position: %1").arg((*slideIter)->position));
        rawData.append(QString("useMarkup: %1").arg(
                           (*slideIter)->useMarkup));
        rawData.append(QString("slideText: %1").arg(
                           (*slideIter)->slideText));
        rawData.append(QString("slideMedia: %1").arg(
                           (*slideIter)->slideMedia));
        rawData.append(QString("backgroundColor: %1").arg(
                           (*slideIter)->backgroundColor));
        rawData.append(QString("slideNumber: %1").arg(
                           (*slideIter)->slideNumber));
        ++slideIter;
    }
    return rawData;

}




}  // namespace pointy
