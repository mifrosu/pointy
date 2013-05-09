#include "slide_list_model.h"
#include "slide_data.h"
#include <QtCore/QtCore>
#include <QMessageLogger>
#include <qregexp.h>
#include <qhash.h>


namespace pointy {
/**
// define custom data roles starting with Qt::UserRole
const int SlideListModel::StageColorRole = Qt::UserRole + 1;
const int SlideListModel::FontRole = Qt::UserRole + 2;
const int SlideListModel::NotesFontRole = Qt::UserRole + 3;
const int SlideListModel::NotesFontSizeRole = Qt::UserRole + 4;
const int SlideListModel::TextColorRole = Qt::UserRole + 5;
const int SlideListModel::TextAlignRole = Qt::UserRole + 6;
const int SlideListModel::ShadingColorRole = Qt::UserRole + 7;
const int SlideListModel::DurationRole = Qt::UserRole + 8;
const int SlideListModel::CommandRole = Qt::UserRole + 9;
const int SlideListModel::TransitionRole = Qt::UserRole + 10;
const int SlideListModel::CameraFrameRateRole = Qt::UserRole + 11;
const int SlideListModel::BackgroundScaleRole = Qt::UserRole + 12;
const int SlideListModel::PositionRole = Qt::UserRole + 13;
const int SlideListModel::UseMarkupRole = Qt::UserRole + 14;
const int SlideListModel::SlideTextRole = Qt::UserRole + 15;
**/


SlideListModel::SlideListModel(QObject *parent) : QAbstractListModel(parent)
{
    settingsMapList = QSharedPointer<stringMapList>(new stringMapList);

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

void populateSlideSettingsMap(QSharedPointer<QStringList>& listIn,
                      QSharedPointer<QMap<QString, QString> >& slideSettings)
{
    if (!listIn || !slideSettings) {
        return;
    }
    QStringList::const_iterator iter;
    QStringList::const_iterator end = listIn->end();

    for (iter = listIn->begin(); iter!=end;++iter)
    {
        int equalsIndex = (*iter).indexOf("=");
        if (equalsIndex > 0) {
            slideSettings->insert((*iter).left(equalsIndex).trimmed(),
                                  (*iter).mid(equalsIndex+ 1).trimmed());
            continue;
        }
        int stopIndex = (*iter).indexOf(".");
        if (stopIndex != -1) {
            // check if file exists?
            slideSettings->insert("slideMedia",(*iter).trimmed());
            continue;
        }
        int markupIndex = (*iter).indexOf("markup");
        if (markupIndex != -1) {
            slideSettings->insert("useMarkup",(*iter).trimmed());
            continue;
        }
        if ((*iter).contains(QRegExp("fill|fit|stretch|unscaled"))) {
            slideSettings->insert("backgroundScaling",(*iter).trimmed());
            continue;
        }
        if ((*iter).contains(QRegExp("top|bottom|left|right|center"))) {
            slideSettings->insert("position", (*iter).trimmed());
            continue;
        }
        else {
            slideSettings->insert("backgroundColor", (*iter).trimmed());
        }
    }

}

void SlideListModel::newSlideSetting()
{
    settingsMapList->push_back(QSharedPointer<QMap<QString,QString> >(
                                   new QMap<QString,QString>));
}


void SlideListModel::readSlideFile(const QString fileName)
{
    int lineCount = 0;      // for error reporting
    bool haveCustomSettings = false;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qFatal("Slide file can not be read");
    }

    QSharedPointer<QStringList> rawSettingsList =
            QSharedPointer<QStringList>(new QStringList);
    newSlideSetting();
    stringMapPtr customSettings = settingsMapList->first();
    newSlideSetting();
    stringMapPtr currentSlideSettings = settingsMapList->last();
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
                populateSlideSettingsMap(rawSettingsList, customSettings);
            }
            if (haveCustomSettings == true) {
                if (!(currentSlideSettings->isEmpty())) {
                    if (!(currentSlideText->isEmpty())) {
                        *currentSlideText = currentSlideText->trimmed();
                        currentSlideSettings->insert("slideText",
                                                        *currentSlideText);
                    }
                }
                newSlideSetting();
                currentSlideSettings = settingsMapList->last();
                rawSettingsList->clear();
                currentSlideText->clear();
            }

            if (linePtr->contains("[")) {
                stripSquareBrackets(linePtr,rawSettingsList, lineCount);
                populateSlideSettingsMap(rawSettingsList,
                                         currentSlideSettings);
            }
        }
        else {
            currentSlideText->append(*linePtr);
        }
    }
    if (!(currentSlideSettings->isEmpty()) ||
            !(currentSlideText->isEmpty())) {
        *currentSlideText = currentSlideText->trimmed();
        currentSlideSettings->insert("slideText",*currentSlideText);
    }

}

QString SlideListModel::getRawSlideData() const
{
    QString rawData;
    rawData.append('\n');
    QList<stringMapPtr>::const_iterator listIter =
            settingsMapList->begin();
    QList<stringMapPtr>::const_iterator endList =
            settingsMapList->end();
    while (listIter != endList) {
        QMap<QString,QString>::const_iterator mapIter = (*listIter)->begin();
        QMap<QString,QString>::const_iterator endMap = (*listIter)->end();
        while (mapIter != endMap) {
            QString outData = mapIter.key() + ": " + mapIter.value() + "\n";
            rawData.append(outData);
            ++mapIter;
        }
        ++listIter;
    }
    return rawData;

}




}  // namespace pointy
