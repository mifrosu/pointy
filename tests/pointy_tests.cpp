#include <QtTest/QtTest>
#include "slide_list_model.h"


/**
 * Test list
 *
 * 1. Slide list model creates a list with a default slide
 * 2. Default values are set correctly
 * 3.
 */


class TestTextParser: public QObject
{
    Q_OBJECT
private slots:
    void stripComments();
};

void TestTextParser::stripComments()
{
    QString testStr = "Hello # and goodbye";
    QString outStr = pointy::stripComments(testStr);
    QCOMPARE(outStr, QString("Hello "));
}


/**
class TestQString: public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
};

void TestQString::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}
**/

QTEST_MAIN(TestTextParser)
#include "pointy_tests.moc"
