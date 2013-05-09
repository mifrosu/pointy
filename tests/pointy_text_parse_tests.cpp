#include "pointy_text_parse_tests.h"
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
    QCOMPARE(*testPtr, QByteArray("Hello \\#and \\#and "));
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
    QCOMPARE(*testPtr, QByteArray("Hello \\#and \\#and "));
}

void TestCommentTextParser::stripCommentsEscapedOutofRange()
{
    testStr = "Hello \\# and \\#";
    *testPtr = testStr;
    pointy::stripComments(testPtr);
    QCOMPARE(*testPtr, QByteArray("Hello \\# and \\#"));
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

TestPopulateMapParser::TestPopulateMapParser()
{
    listInPtr = QSharedPointer<QStringList> (new QStringList);
    slideMapPtr =
            QSharedPointer<QMap<QString,QString> >(new QMap<QString,QString>);

}

void TestPopulateMapParser::populateSlideMapEquals()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    listInPtr->append("font=monospace 18px");
    expectMap.insert("font","monospace 18px");
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
}

void TestPopulateMapParser::populateSlideMapEqualsMulti()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    listInPtr->append("font=monospace 18px");
    listInPtr->append("duration=5.000000");
    expectMap.insert("font","monospace 18px");
    expectMap.insert("duration","5.000000");
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
}

void TestPopulateMapParser::populateSlideMapMedia()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    QString test1("doctorwho_blink.jpeg");
    listInPtr->append(test1);
    expectMap.insert("slideMedia",test1);
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
}

void TestPopulateMapParser::populateSlideMapBackgroundScalingFill()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    QString test1("fill");
    listInPtr->append(test1);
    expectMap.insert("backgroundScaling",test1);
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
}


void TestPopulateMapParser::populateSlideMapBackgroundScalingFit()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    QString test1("fit");
    listInPtr->append(test1);
    expectMap.insert("backgroundScaling",test1);
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
}

void TestPopulateMapParser::populateSlideMapBackgroundScalingStretch()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    QString test1("stretch");
    listInPtr->append(test1);
    expectMap.insert("backgroundScaling",test1);
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
}

void TestPopulateMapParser::populateSlideMapBackgroundScalingUnscaled()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    QString test1("unscaled");
    listInPtr->append(test1);
    expectMap.insert("backgroundScaling",test1);
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
}

void TestPopulateMapParser::populateSlideMapPositionBottomLeft()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    QString test1("bottom-left");
    listInPtr->append(test1);
    expectMap.insert("position",test1);
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
}

void TestPopulateMapParser::populateSlideMapPositionTopRight()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    QString test1("top-right");
    listInPtr->append(test1);
    expectMap.insert("position",test1);
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
}

void TestPopulateMapParser::populateSlideMapPositionCenter()
{
    QMap<QString, QString> expectMap;
    QList<QString> expectKeys;
    QList<QString> expectValues;
    listInPtr->clear();
    slideMapPtr->clear();
    QString test1("center");
    listInPtr->append(test1);
    expectMap.insert("position",test1);
    expectKeys = expectMap.keys();
    expectValues = expectMap.values();
    pointy::populateSlideSettingsMap(listInPtr, slideMapPtr);
    QCOMPARE(slideMapPtr->keys(),expectKeys);
    QCOMPARE(slideMapPtr->values(),expectValues);
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
