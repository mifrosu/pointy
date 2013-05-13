#ifndef POINTY_TEXT_PARSE_TESTS_H
#define POINTY_TEXT_PARSE_TESTS_H

#include <QtTest/QtTest>

class TestCommentTextParser: public QObject
{
    Q_OBJECT

public:
    TestCommentTextParser();

private:
    int lineCount;
    QByteArray testStr;
    QSharedPointer<QByteArray> testPtr;

private slots:
    void stripCommentsMiddle();
    void stripCommentsStart();
    void stripCommentsNoComment();
    void stripCommentsMultiComment();
    void stripCommentsEscaped();
    void stripCommentsFile();
    void stripCommentsEscapedOutofRange();
};

class TestSquareBracketParser: public QObject
{
    Q_OBJECT
public:
    TestSquareBracketParser();

private:
    QSharedPointer<QByteArray> linePtr;
    QSharedPointer<QStringList> storePtr;
    QSharedPointer<int> lineCountPtr;

private slots:
    void stripSquareBracketsNoBrackets();
    void stripSquareBracketsOneSetting();
    void stripSquareBracketsThreeSettings();
    void stripSquareBracketsSettingsWithJunk();
    void stripSquareBracketsMalformedStart();
    void stripSquareBracketsMalformedEnd();

};



#endif // POINTY_TEXT_PARSE_TESTS_H
