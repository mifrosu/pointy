#include "slide_list_model.h"
#include "slide_data.h"

namespace pointy {
/**
// define custom data roles starting with Qt::UserRole
const int SlideListModel::StageColorRole = Qt::UserRole + 1;
const int SlideListModel::Font = Qt::UserRole + 2;
const int SlideListModel::NotesFont = Qt::UserRole + 3;
const int SlideListModel::NotesFontSize = Qt::UserRole + 4;
const int SlideListModel::TextColor = Qt::UserRole + 5;
const int SlideListModel::TextAlign = Qt::UserRole + 6;
const int SlideListModel::ShadingColor = Qt::UserRole + 7;
const int SlideListModel::Duration = Qt::UserRole + 8;
const int SlideListModel::Command = Qt::UserRole + 9;
const int SlideListModel::Transition = Qt::UserRole + 10;
const int SlideListModel::CameraFrameRate = Qt::UserRole + 11;
const int SlideListModel::BackgroundScale = Qt::UserRole + 12;
const int SlideListModel::Position = Qt::UserRole + 13;
const int SlideListModel::UseMarkup = Qt::UserRole + 14;
const int SlideListModel::SlideText = Qt::UserRole + 15;
**/

int SlideListModel::rowCount(const QModelIndex /*&parent*/) const
{
    return slideList.size();
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
