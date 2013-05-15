#include "pointy_text_parse_tests.h"
#include "slide_data.h"
#include "slide_list_model.h"


TestCommentTextParser::TestCommentTextParser()
{
    testPtr = QSharedPointer<QByteArray>(new QByteArray);

}

void TestCommentTextParser::stripCommentsMiddle()
{
    testStr = "Hello # and goodbye";
    *testPtr = testStr;
    pointy::stripComments(testPtr);
    QCOMPARE(*testPtr, QByteArray("Hello "));
}

void TestCommentTextParser::stripCommentsStart()
{
    testStr = "#Hello and goodbye";
    *testPtr = testStr;
    pointy::stripComments(testPtr);
    QCOMPARE(*testPtr, QByteArray());
}

void TestCommentTextParser::stripCommentsNoComment()
{
    testStr = "Hello and goodbye";
    *testPtr = testStr;
    pointy::stripComments(testPtr);
    QCOMPARE(*testPtr, QByteArray("Hello and goodbye"));
}

void TestCommentTextParser::stripCommentsMultiComment()
{
    testStr = "Hello #and #goodbye";
    *testPtr = testStr;
    pointy::stripComments(testPtr);
    QCOMPARE(*testPtr, QByteArray("Hello "));
}

void TestCommentTextParser::stripCommentsEscaped()
{
    testStr = "Hello \\#and \\#and #goodbye";
    *testPtr = testStr;
    pointy::stripComments(testPtr);
    QCOMPARE(*testPtr, QByteArray("Hello #and #and "));
}


void TestCommentTextParser::stripCommentsFile()
{
    QFile file(":/test_input_files/comment_test_file.pin");
    if (!file.open(QIODevice::ReadOnly)) {
        qFatal("Slide file can not be read");
    }
    testStr = file.readLine();
    *testPtr = testStr;
    pointy::stripComments(testPtr);
    QCOMPARE(*testPtr, QByteArray("Hello #and #and "));
}

void TestCommentTextParser::stripCommentsEscapedOutofRange()
{
    testStr = "Hello \\# and \\#";
    *testPtr = testStr;
    pointy::stripComments(testPtr);
    QCOMPARE(*testPtr, QByteArray("Hello # and #"));
}

TestSquareBracketParser::TestSquareBracketParser()
{
    linePtr = QSharedPointer<QByteArray>(new QByteArray);
    storePtr = QSharedPointer<QStringList>(new QStringList);
    lineCountPtr = QSharedPointer<int>(new int);
    *lineCountPtr = 1;

}

void TestSquareBracketParser::stripSquareBracketsNoBrackets()
{
    linePtr->clear();
    storePtr->clear();
    linePtr->append("no brackets here");
    pointy::stripSquareBrackets(linePtr, storePtr, *lineCountPtr);
    QCOMPARE(*storePtr, QStringList());
}

void TestSquareBracketParser::stripSquareBracketsOneSetting()
{
    linePtr->clear();
    storePtr->clear();
    linePtr->append("[one bracket here]");
    pointy::stripSquareBrackets(linePtr, storePtr, *lineCountPtr);
    QCOMPARE(*storePtr, QStringList("one bracket here"));
}

void TestSquareBracketParser::stripSquareBracketsThreeSettings()
{
    QStringList expectedStore;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    expectedStore.append("third setting");
    linePtr->clear();
    storePtr->clear();
    linePtr->append("[first setting][second setting][third setting]");
    pointy::stripSquareBrackets(linePtr, storePtr, *lineCountPtr);
    qDebug() << "*** StorePtr" << *storePtr << '\n';
    QCOMPARE(*storePtr, expectedStore);
}

void TestSquareBracketParser::stripSquareBracketsSettingsWithJunk()
{
    QStringList expectedStore;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    expectedStore.append("third setting");
    linePtr->clear();
    storePtr->clear();
    linePtr->append("[first setting]junk[second setting]meh[third setting]");
    pointy::stripSquareBrackets(linePtr, storePtr, *lineCountPtr);
    QCOMPARE(*storePtr, expectedStore);
}

void TestSquareBracketParser::stripSquareBracketsMalformedStart()
{
    QStringList expectedStore;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    expectedStore.append("third setting");
    linePtr->clear();
    storePtr->clear();
    linePtr->append("first setting]junk[second setting]meh[third setting]");
    pointy::stripSquareBrackets(linePtr, storePtr, *lineCountPtr);
    QCOMPARE(*storePtr, QStringList());
}

void TestSquareBracketParser::stripSquareBracketsMalformedEnd()
{
    QStringList expectedStore;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    expectedStore.append("third setting");
    linePtr->clear();
    storePtr->clear();
    linePtr->append("[first settingjunk[second setting]meh[third setting]");
    pointy::stripSquareBrackets(linePtr, storePtr, *lineCountPtr);
    QCOMPARE(*storePtr, QStringList());
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
