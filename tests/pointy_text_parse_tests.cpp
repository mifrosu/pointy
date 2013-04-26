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

void TestTextParser::heapTest()
{
    QByteArray testStr = "Hello # and goodbye";
    QSharedPointer<QByteArray> testPtr =
            QSharedPointer<QByteArray>(new QByteArray);
    *testPtr = testStr;
    pointy::stripComments(&(*testPtr));
    QCOMPARE(*testPtr, QByteArray("Hello "));
}

void TestTextParser::stripCommentsMiddle()
{
    QByteArray testStr = "Hello # and goodbye";
    pointy::stripComments(&testStr);
    QCOMPARE(testStr, QByteArray("Hello "));
}

void TestTextParser::stripCommentsStart()
{
    QByteArray testStr = "#Hello and goodbye";
    pointy::stripComments(&testStr);
    QCOMPARE(testStr, QByteArray());
}

void TestTextParser::stripCommentsNoComment()
{
    QByteArray testStr = "Hello and goodbye";
    pointy::stripComments(&testStr);
    QCOMPARE(testStr, QByteArray("Hello and goodbye"));
}

void TestTextParser::stripCommentsMultiComment()
{
    QByteArray testStr = "Hello #and #goodbye";
    pointy::stripComments(&testStr);
    QCOMPARE(testStr, QByteArray("Hello "));
}

void TestTextParser::stripCommentsEscaped()
{
    QByteArray testStr = "Hello \\#and \\#and #goodbye";
    pointy::stripComments(&testStr);
    QCOMPARE(testStr, QByteArray("Hello \\#and \\#and "));
}


void TestTextParser::stripCommentsFile()
{
    QFile file(":/test_input_files/comment_test_file.pin");
    if (!file.open(QIODevice::ReadOnly)) {
        qFatal("Slide file can not be read");
    }
    QByteArray line = file.readLine();
    pointy::stripComments(&line);
    QCOMPARE(line, QByteArray("Hello \\#and \\#and "));
}

void TestTextParser::stripCommentsEscapedOutofRange()
{
    QByteArray testStr = "Hello \\# and \\#";
    pointy::stripComments(&testStr);
    QCOMPARE(testStr, QByteArray("Hello \\# and \\#"));
}

void TestTextParser::stripSquareBracketsNoBrackets()
{
    QStringList store;
    QByteArray lineIn("no brackets here");
    pointy::stripSquareBrackets(&lineIn, &store, &lineCount);
    QCOMPARE(store, QStringList());
}

void TestTextParser::stripSquareBracketsOneSetting()
{
    QStringList store;
    QByteArray lineIn("[one bracket here]");
    pointy::stripSquareBrackets(&lineIn, &store, &lineCount);
    QCOMPARE(store, QStringList("one bracket here"));
}

void TestTextParser::stripSquareBracketsTwoSettings()
{
    QStringList store;
    QStringList expectedStore;
    expectedStore.append("first setting");
    expectedStore.append("second setting");
    QByteArray lineIn("[first setting][second setting]");
    pointy::stripSquareBrackets(&lineIn, &store, &lineCount);
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
    pointy::stripSquareBrackets(&lineIn, &store, &lineCount);
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
    pointy::stripSquareBrackets(&lineIn, &store, &lineCount);
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
    pointy::stripSquareBrackets(&lineIn, &store, &lineCount);
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
    pointy::stripSquareBrackets(&lineIn, &store, &lineCount);
    QCOMPARE(store, QStringList());
}

void TestTextParser::populateSlideMapEquals()
{
    QStringList listIn;
    listIn.append("font=monospace 18px");
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("font","monospace 18px");
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
}

void TestTextParser::populateSlideMapEqualsMulti()
{
    QStringList listIn;
    listIn.append("font=monospace 18px");
    listIn.append("duration=5.000000");
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("font","monospace 18px");
    expectMap.insert("duration","5.000000");
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
}

void TestTextParser::populateSlideMapMedia()
{
    QStringList listIn;
    QString test1("doctorwho_blink.jpeg");
    listIn.append(test1);
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("slideMedia",test1);
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
}

void TestTextParser::populateSlideMapBackgroundScalingFill()
{
    QStringList listIn;
    QString test1("fill");
    listIn.append(test1);
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("backgroundScaling",test1);
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
}


void TestTextParser::populateSlideMapBackgroundScalingFit()
{
    QStringList listIn;
    QString test1("fit");
    listIn.append(test1);
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("backgroundScaling",test1);
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
}

void TestTextParser::populateSlideMapBackgroundScalingStretch()
{
    QStringList listIn;
    QString test1("stretch");
    listIn.append(test1);
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("backgroundScaling",test1);
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
}

void TestTextParser::populateSlideMapBackgroundScalingUnscaled()
{
    QStringList listIn;
    QString test1("unscaled");
    listIn.append(test1);
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("backgroundScaling",test1);
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
}

void TestTextParser::populateSlideMapPositionBottomLeft()
{
    QStringList listIn;
    QString test1("bottom-left");
    listIn.append(test1);
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("position",test1);
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
}

void TestTextParser::populateSlideMapPositionTopRight()
{
    QStringList listIn;
    QString test1("top-right");
    listIn.append(test1);
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("position",test1);
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
}

void TestTextParser::populateSlideMapPositionCenter()
{
    QStringList listIn;
    QString test1("center");
    listIn.append(test1);
    QMap<QString, QString> slideMap;
    QMap<QString, QString> expectMap;
    expectMap.insert("position",test1);
    pointy::populateSlideSettingsMap(&listIn, &slideMap);
    QList<QString> slideKeys = slideMap.keys();
    QList<QString> expectKeys = expectMap.keys();
    QList<QString> slideValues = slideMap.values();
    QList<QString> expectValues = expectMap.values();
    QCOMPARE(slideKeys,expectKeys);
    QCOMPARE(slideValues,expectValues);
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
