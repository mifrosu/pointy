#include "pointy_text_parse_tests.h"
#include "slide_list_model.h"


/**
 * Test list
 *
 * 1. Slide list model creates a list with a default slide
 * 2. Default values are set correctly
 * 3.
 */


//class TestTextParser: public QObject
//{
//    Q_OBJECT
//private slots:
//    void stripCommentsMiddle();
//    void stripCommentsStart();
//    void stripCommentsNoComment();
//    void stripCommentsMultiComment();
//    void stripCommentsEscaped();
//    void stripCommentsFile();
//};

void TestTextParser::stripCommentsMiddle()
{
    QByteArray testStr = "Hello # and goodbye";
    QByteArray outStr = pointy::stripComments(testStr);
    QCOMPARE(outStr, QByteArray("Hello "));
}

void TestTextParser::stripCommentsStart()
{
    QByteArray testStr = "#Hello and goodbye";
    QByteArray outStr = pointy::stripComments(testStr);
    QCOMPARE(outStr, QByteArray());
}

void TestTextParser::stripCommentsNoComment()
{
    QByteArray testStr = "Hello and goodbye";
    QByteArray outStr = pointy::stripComments(testStr);
    QCOMPARE(outStr, QByteArray("Hello and goodbye"));
}

void TestTextParser::stripCommentsMultiComment()
{
    QByteArray testStr = "Hello #and #goodbye";
    QByteArray outStr = pointy::stripComments(testStr);
    QCOMPARE(outStr, QByteArray("Hello "));
}

void TestTextParser::stripCommentsEscaped()
{
    QByteArray testStr = "Hello \\#and \\#and #goodbye";
    QByteArray outStr = pointy::stripComments(testStr);
    QCOMPARE(outStr, QByteArray("Hello \\#and \\#and "));
}


void TestTextParser::stripCommentsFile()
{
    QFile file(":/test_input_files/comment_test_file.pin");
    if (!file.open(QIODevice::ReadOnly)) {
        qFatal("Slide file can not be read");
    }
    QByteArray line = file.readLine();
    QByteArray outStr = pointy::stripComments(line);
    QCOMPARE(outStr, QByteArray("Hello \\#and \\#and "));
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

//QTEST_MAIN(TestTextParser)
//#include "pointy_tests.moc"
