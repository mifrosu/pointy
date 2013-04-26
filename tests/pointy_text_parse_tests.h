#ifndef POINTY_TEXT_PARSE_TESTS_H
#define POINTY_TEXT_PARSE_TESTS_H

#include <QtTest/QtTest>

class TestTextParser: public QObject
{
    Q_OBJECT

    int lineCount;
private slots:
    void stripCommentsMiddle();
    void stripCommentsStart();
    void stripCommentsNoComment();
    void stripCommentsMultiComment();
    void stripCommentsEscaped();
    void stripCommentsFile();
    void stripCommentsEscapedOutofRange();

    void stripSquareBracketsNoBrackets();
    void stripSquareBracketsOneSetting();
    void stripSquareBracketsTwoSettings();
    void stripSquareBracketsThreeSettings();
    void stripSquareBracketsSettingsWithJunk();
    void stripSquareBracketsMalformedStart();
    void stripSquareBracketsMalformedEnd();

    void populateSlideMapEquals();
    void populateSlideMapEqualsMulti();
    void populateSlideMapMedia();
    void populateSlideMapBackgroundScalingFill();
    void populateSlideMapBackgroundScalingFit();
    void populateSlideMapBackgroundScalingStretch();
    void populateSlideMapBackgroundScalingUnscaled();
    void populateSlideMapPositionBottomLeft();
    void populateSlideMapPositionTopRight();
    void populateSlideMapPositionCenter();

    void heapTest();



    
};



#endif // POINTY_TEXT_PARSE_TESTS_H
