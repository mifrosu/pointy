#include "slide_list_model.h"
#include "slide_data.h"
#include <QtCore/QtCore>
#include <QMessageLogger>


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

int SlideListModel::rowCount(const QModelIndex /*&parent*/) const
{
    return slideList.size();
}

void stripComments(QByteArray* lineIn, const QString comment)
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
        QByteArray remains = (lineIn->mid(commentIndex + 1));
        stripComments(&remains);
        *lineIn = (lineIn->left(commentIndex + 1)).append(remains);
    }
    else {
        *lineIn = (lineIn->left(commentIndex));
    }
}

void stripSquareBrackets(QByteArray* lineIn,
                         QStringList* store,
                         int* lineCount)
{
    int numberStartBracket = lineIn->count("[");
    int numberEndBracket = lineIn->count("]");
    if (numberStartBracket != numberEndBracket)
    {
        qWarning("Line %d: incomplete brackets", *lineCount);
        return;
    }
    int startBracket = lineIn->indexOf("[");
    if (startBracket < 0) {
        return;
    }

    int endBracket = lineIn->indexOf("]");
    if (endBracket < startBracket) {
        qWarning("Line %d: mismatched brackets", *lineCount);
        return;
    }
    QByteArray remains = (lineIn->mid(endBracket + 1));
    store->append(lineIn->mid(startBracket + 1, endBracket-(startBracket+1)));
    // recursive search for additional settings on the line
    stripSquareBrackets(&remains,
                        store, lineCount);
}

void populateSlideMap(const QStringList *listIn,
                      QMap<QString, QString> *slideSettings);

//void setSlideSettingsMap(const QByteArray line, bool& isNewSlideShow,
//                         QMap<QString, QString>& slideSettings)
//{
//    if (line.startsWith("[") && isNewSlideShow == true)
//    {

//    }


//}


//void SlideListModel::readSlideFile(const QString fileName)
//{
//    lineCount = 0;      // for error reporting
//    haveCustomSettings = false;

//    QFile file(fileName);
//    if (!file.open(QIODevice::ReadOnly)) {
//        qFatal("Slide file can not be read");
//        //return 1;
//    }

//    while (!file.atEnd()) {
//        ++lineCount;
//        QByteArray line = file.readLine();
//        line = stripComments(line, "#");
//        // processLine
        // process function
//        if (line.startsWith("[") && settingsFlag == false) {
//            // strip []
//            //

//        }
//        if (line.startsWith("--") && settingsFlag == false) {
//            settingsFlag = true;
//            // apply currentSettings map to default slide (with function)

//            // makeSlide function --- process map
//            // ... clear map
//            // ... new map = copy of default map
//        }
//        else {
//            // slide body -- add to current map
//        }
//    }

//}








QVariant SlideListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();      // return a Null variant

    if (index.row() >= slideList.size() )
        return QVariant();

    const QSharedPointer<SlideData> currentSlide = slideList.at(index.row());
    switch (role) {
    case StageColorRole:
        return QVariant::fromValue(currentSlide->stage_color);
    case FontRole:
        return QVariant::fromValue(currentSlide->font);
    case NotesFontRole:
        return QVariant::fromValue(currentSlide->notes_font);
    case NotesFontSizeRole:
        return QVariant::fromValue(currentSlide->notes_font_size);
    case TextColorRole:
        return QVariant::fromValue(currentSlide->text_color);
    case TextAlignRole:
        return QVariant::fromValue(currentSlide->text_align);
    case ShadingColorRole:
        return QVariant::fromValue(currentSlide->shading_color);
    case ShadingOpacityRole:
        return QVariant::fromValue(currentSlide->shading_opacity);
    case DurationRole:
        return QVariant::fromValue(currentSlide->duration);
    case CommandRole:
        return QVariant::fromValue(currentSlide->command);
    case TransitionRole:
        return QVariant::fromValue(currentSlide->transition);
    case CameraFrameRateRole:
        return QVariant::fromValue(currentSlide->camera_frame_rate);
    case BackgroundScaleRole:
        return QVariant::fromValue(currentSlide->background_scale);
    case PositionRole:
        return QVariant::fromValue(currentSlide->position);
    case UseMarkupRole:
        return QVariant::fromValue(currentSlide->use_markup);
    case SlideTextRole:
        return QVariant::fromValue(currentSlide->slide_text);
    case SlideMediaRole:
        return QVariant::fromValue(currentSlide->slide_media);
    default:
        return QVariant();
    }
}


}
