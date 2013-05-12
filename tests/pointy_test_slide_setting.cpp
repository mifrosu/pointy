#include "pointy_test_slide_setting.h"

namespace pointy {



TestSlideSetting::TestSlideSetting()
{

     testSlide = QSharedPointer<SlideData>(new SlideData);
}

void TestSlideSetting::assignSlideSettings()
{
    slideSettingEquals("stage-color "," black", testSlide);
    QCOMPARE(testSlide->stageColor, QString("black"));
    slideSettingEquals("font", "Sans 50 px", testSlide);
    QCOMPARE(testSlide->font, QString("Sans 50 px"));
    slideSettingEquals("notes-font", "Sans ", testSlide);
    QCOMPARE(testSlide->notesFont, QString("Sans"));
    slideSettingEquals("notes-font-size","100 px", testSlide);
    QCOMPARE(testSlide->notesFontSize, QString("100 px"));
    slideSettingEquals("text-color", "crimson", testSlide);
    QCOMPARE(testSlide->textColor, QString("crimson"));
    slideSettingEquals("text-align","left", testSlide);
    QCOMPARE(testSlide->textAlign, QString("left"));
    slideSettingEquals("shading-color", "blue", testSlide);
    QCOMPARE(testSlide->shadingColor, QString("blue"));

    slideSettingEquals("shading-opacity","0.5", testSlide);
    QCOMPARE(testSlide->shadingOpacity, qreal(0.5));
    slideSettingEquals("duration","0.1", testSlide);
    QCOMPARE(testSlide->duration, float(0.1));
    slideSettingEquals("transition", "slide", testSlide);
    QCOMPARE(testSlide->transition, QString("slide"));
    slideSettingEquals("camera-framerate","20", testSlide);
    QCOMPARE(testSlide->cameraFrameRate, int(20));
}


} // namespace pointy
