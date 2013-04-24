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

    // malformed 1: one ]
    // malformed 2: one [
    void stripSquareBracketsNoBrackets();
    void stripSquareBracketsOneSetting();
    void stripSquareBracketsTwoSettings();
    void stripSquareBracketsThreeSettings();
    void stripSquareBracketsSettingsWithJunk();
    void stripSquareBracketsMalformedStart();
    void stripSquareBracketsMalformedEnd();

    
};



#endif // POINTY_TEXT_PARSE_TESTS_H
