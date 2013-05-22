#ifndef SLIDE_LIST_MODEL_H
#define SLIDE_LIST_MODEL_H

#include <QAbstractListModel>
#include "slide_data.h"
#include <qvariant.h>
//#include <qscopedpointer.h>
#include <qsharedpointer.h>
#include <qmap.h>
#include <qstring.h>
#include <qstringlist.h>



namespace pointy {

class SlideData;

class SlideListModel: public QAbstractListModel
{
    Q_OBJECT

public:
    SlideListModel(QObject* parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent= QModelIndex()) const;
    void readSlideFile(const QString fileName);
    QStringList getRawSlideData() const;

    void clearSlides();

    enum SlideRoles {
        StageColorRole = Qt::UserRole + 1,
        FontRole,
        FontSizeRole,
        FontSizeUnitRole,
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
        MaxLineLengthRole,
        SlideMediaRole,
        BackgroundColorRole,
        NotesTextRole,
        SlideNumberRole
    };


private:
    Q_DISABLE_COPY(SlideListModel)

    QHash<int, QByteArray> roleNames() const;

    QSharedPointer<SlideData> customSlideSettings;
    QList<QSharedPointer<SlideData> > slideList;

    void populateSlideList(QStringList& listIn,
                           QSharedPointer<SlideData>& slide);
    void newSlideSetting();
    void newSlideSetting(const SlideData& customSlideSettings);


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

void stripComments(QSharedPointer<QByteArray>& lineIn,
                   QSharedPointer<QString>& commentStore,
                   const QString comment="#");
void stripSquareBrackets(QSharedPointer<QByteArray>& lineIn,
                         QSharedPointer<QStringList>& store,
                         const int &lineCount);

void populateSlideSettingsMap(QSharedPointer<QStringList>& listIn,
                      QSharedPointer<QMap<QString, QString> >& slideSettings);

void populateSlideSettings(QStringList& listIn,
                           QSharedPointer<SlideData>& currentSlide);

void findMaxLineLength(QSharedPointer<QByteArray>& lineIn, int& lineLength);



}

#endif // SLIDE_LIST_MODEL_H
