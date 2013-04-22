#include <QtTest/QtTest>
#include <iostream>

/**
 * Test list
 *
 * 1. Slide list model creates a list with a default slide
 * 2. Default values are set correctly
 * 3.
 */

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


QTEST_MAIN(TestQString)
#include "pointy_tests.moc"
