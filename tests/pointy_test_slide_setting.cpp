#include "pointy_test_slide_setting.h"

namespace pointy {

TestSlideSetting::TestSlideSetting()
{

     testSlide = QSharedPointer<SlideData>(new SlideData);
}

void TestSlideSetting::setFontTest()
{
    testSlide->setFont("Monospace 100 px");
    QCOMPARE(testSlide->font, QString("monospace"));
    QCOMPARE(testSlide->fontSize, qreal(100));
    QCOMPARE(testSlide->fontSizeUnit, QString("px"));
}

void TestSlideSetting::assignSlideSettings()
{
    testSlide->slideSettingAssign("stage-color "," red");
    QCOMPARE(testSlide->stageColor, QString("red"));
    testSlide->slideSettingAssign("font", "Sans 50 px");
    QCOMPARE(testSlide->font, QString("sans"));
    QCOMPARE(testSlide->fontSize, qreal(50));
    QCOMPARE(testSlide->fontSizeUnit, QString("px"));
    testSlide->slideSettingAssign("notes-font", "Sans ");
    QCOMPARE(testSlide->notesFont, QString("Sans"));
    testSlide->slideSettingAssign("notes-font-size","100 px");
    QCOMPARE(testSlide->notesFontSize, QString("100 px"));
    testSlide->slideSettingAssign("text-color", "crimson");
    QCOMPARE(testSlide->textColor, QString("crimson"));
    testSlide->slideSettingAssign("text-align","left");
    QCOMPARE(testSlide->textAlign, QString("left"));
    testSlide->slideSettingAssign("shading-color", "red");
    QCOMPARE(testSlide->shadingColor, QString("red"));

    testSlide->slideSettingAssign("shading-opacity","0.5");
    QCOMPARE(testSlide->shadingOpacity, qreal(0.5));
    testSlide->slideSettingAssign("duration","0.1");
    QCOMPARE(testSlide->duration, float(0.1));
    testSlide->slideSettingAssign("transition", "slide");
    QCOMPARE(testSlide->transition, QString("slide"));
    testSlide->slideSettingAssign("camera-framerate","20");
    QCOMPARE(testSlide->cameraFrameRate, int(20));

    testSlide->slideSettingAssign("inPictura.jpeg ");
    QCOMPARE(testSlide->slideMedia, QString("inPictura.jpeg"));
    testSlide->slideSettingAssign("no-markup");
    QCOMPARE(testSlide->useMarkup, false);
    testSlide->slideSettingAssign("stretch");
    QCOMPARE(testSlide->backgroundScale, QString("stretch"));

    testSlide->slideSettingAssign("top-left");
    QCOMPARE(testSlide->position, QString("top-left"));
    testSlide->slideSettingAssign("top-right");
    QCOMPARE(testSlide->position, QString("top-right"));
    testSlide->slideSettingAssign("top");
    QCOMPARE(testSlide->position, QString("top"));
    testSlide->slideSettingAssign("left");
    QCOMPARE(testSlide->position, QString("left"));
    testSlide->slideSettingAssign("right");
    QCOMPARE(testSlide->position, QString("right"));
    testSlide->slideSettingAssign("center");
    QCOMPARE(testSlide->position, QString("center"));
    testSlide->slideSettingAssign("bottom-left");
    QCOMPARE(testSlide->position, QString("bottom-left"));
    testSlide->slideSettingAssign("bottom");
    QCOMPARE(testSlide->position, QString("bottom"));
    testSlide->slideSettingAssign("bottom-right");
    QCOMPARE(testSlide->position, QString("bottom-right"));
    testSlide->slideSettingAssign("zebra");
    QCOMPARE(testSlide->backgroundColor, QString("white"));
    testSlide->slideSettingAssign("lightsteelblue");
    QCOMPARE(testSlide->backgroundColor, QString("lightsteelblue"));



}


} // namespace pointy
