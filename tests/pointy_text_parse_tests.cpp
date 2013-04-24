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

void TestTextParser::stripCommentsEscapedOutofRange()
{
    QByteArray testStr = "Hello \\# and \\#";
    QByteArray outStr = pointy::stripComments(testStr);
    QCOMPARE(outStr, QByteArray("Hello \\# and \\#"));
}

void TestTextParser::stripSquareBracketsNoBrackets()
{
    QStringList store;
    QByteArray lineIn("no brackets here");
    pointy::stripSquareBrackets(lineIn, store, lineCount);
    QCOMPARE(store, QStringList());
}

void TestTextParser::stripSquareBracketsOneSetting()
{
    QStringList store;
    QByteArray lineIn("[one bracket here]");
    pointy::stripSquareBrackets(lineIn, store, lineCount);
    QCOMPARE(store, QStringList("one bracket here"));
}

void TestTextParser::stripSquareBracketsTwoSettings()
{
    QStringList store;
    QStringList expectedStore;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    QByteArray lineIn("[first setting][second setting]");
    pointy::stripSquareBrackets(lineIn, store, lineCount);
    QCOMPARE(store, expectedStore);
}

void TestTextParser::stripSquareBracketsThreeSettings()
{
    QStringList store;
    QStringList expectedStore;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    expectedStore.append("third setting");
    QByteArray lineIn("[first setting][second setting][third setting]");
    pointy::stripSquareBrackets(lineIn, store, lineCount);
    QCOMPARE(store, expectedStore);
}

void TestTextParser::stripSquareBracketsSettingsWithJunk()
{
    QStringList store;
    QStringList expectedStore;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    expectedStore.append("third setting");
    QByteArray lineIn("[first setting]junk[second setting]meh[third setting]");
    pointy::stripSquareBrackets(lineIn, store, lineCount);
    QCOMPARE(store, expectedStore);
}

void TestTextParser::stripSquareBracketsMalformedStart()
{
    QStringList store;
    QStringList expectedStore;
    lineCount = 1;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    expectedStore.append("third setting");
    QByteArray lineIn("first setting]junk[second setting]meh[third setting]");
    pointy::stripSquareBrackets(lineIn, store, lineCount);
    QCOMPARE(store, QStringList());
}

void TestTextParser::stripSquareBracketsMalformedEnd()
{
    QStringList store;
    QStringList expectedStore;
    lineCount = 1;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    expectedStore.append("third setting");
    QByteArray lineIn("[first settingjunk[second setting]meh[third setting]");
    pointy::stripSquareBrackets(lineIn, store, lineCount);
    QCOMPARE(store, QStringList());
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
