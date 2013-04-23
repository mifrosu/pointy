#ifndef SLIDE_LIST_MODEL_H
#define SLIDE_LIST_MODEL_H

#include <QAbstractListModel>
#include "slide_data.h"
#include <qvariant.h>
//#include <qscopedpointer.h>
#include <qsharedpointer.h>
#include <qmap.h>
#include <qstring.h>


namespace pointy {

class SlideData;

class SlideListModel: public QAbstractListModel
{
    Q_OBJECT

public:
    SlideListModel(QObject* parent=0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex = QModelIndex()) const;
    void readSlideFile(const QString fileName);

private:
    Q_DISABLE_COPY(SlideListModel)

    //SlideData newSlide();
    //void appendSlide(SlideData currentSlide);

    QList<QSharedPointer<SlideData> > slideList;
    bool haveCustomSettings;

    enum SlideRoles {
        StageColorRole = Qt::UserRole + 1,
        FontRole,
        NotesFontRole,
        NotesFontSizeRole,
        TextColorRole,
        TextAlignRole,
        ShadingColorRole,
        ShadingOpacityRole,
        DurationRole,
        CommandRole,
        TransitionRole,
        CameraFrameRateRole,
        BackgroundScaleRole,
        PositionRole,
        UseMarkupRole,
        SlideTextRole,
        SlideMediaRole
    };

    QMap<SlideRoles, QString> defaultSettings;
    QMap<SlideRoles, QString> currentSlideSettings;


    /**
    static const int StageColorRole;		// transition tint
    static const int Font;
    static const int NotesFont;
    static const int NotesFontSize;
    static const int TextColor;
    static const int TextAlign;
    static const int ShadingColor; 		// text rectangle bground color
    static const int ShadingOpacity;
    static const int Duration;
    static const int Command;
    static const int Transition;
    static const int CameraFrameRate;
    static const int BackgroundScale;
    static const int Position;
    static const int UseMarkup;
    static const int SlideText;
**/
};

QByteArray stripComments(const QByteArray lineIn, const QString comment="#");



}

#endif // SLIDE_LIST_MODEL_H
