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
    QSharedPointer<QString> notesPtr;

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

class TestMaxLineLength: public QObject
{
    Q_OBJECT
public:
    TestMaxLineLength();

private:
    QSharedPointer<QByteArray> linePtr;
    int lineLength;

private slots:
    void checkLineLength();

};



#endif // POINTY_TEXT_PARSE_TESTS_H
