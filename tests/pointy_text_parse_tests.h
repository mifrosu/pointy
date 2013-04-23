#ifndef POINTY_TEXT_PARSE_TESTS_H
#define POINTY_TEXT_PARSE_TESTS_H

#include <QtTest/QtTest>

class TestTextParser: public QObject
{
    Q_OBJECT
private slots:
    void stripCommentsMiddle();
    void stripCommentsStart();
    void stripCommentsNoComment();
    void stripCommentsMultiComment();
    void stripCommentsEscaped();
    void stripCommentsFile();
};



#endif // POINTY_TEXT_PARSE_TESTS_H
