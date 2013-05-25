/*  
 *  This file is part of Pointy.
 *
 *  Copyright (C) 2013 Michael O'Sullivan 
 *
 *  Pointy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Pointy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Pointy.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Written by: Michael O'Sullivan
 */


#include "pointy_text_parse_tests.h"
#include "slide_data.h"
#include "slide_list_model.h"


TestCommentTextParser::TestCommentTextParser()
{
    testPtr = QSharedPointer<QByteArray>(new QByteArray);
    notesPtr = QSharedPointer<QString>(new QString);

}

void TestCommentTextParser::stripCommentsMiddle()
{
    testStr = "Hello # and goodbye";
    *testPtr = testStr;
    pointy::stripComments(testPtr, notesPtr);
    QCOMPARE(*testPtr, QByteArray("Hello "));
    QCOMPARE(*notesPtr, QString(" and goodbye"));
}

void TestCommentTextParser::stripCommentsStart()
{
    testStr = "#Hello and goodbye";
    *testPtr = testStr;
    notesPtr->clear();
    pointy::stripComments(testPtr, notesPtr);
    QCOMPARE(*testPtr, QByteArray());
    QCOMPARE(*notesPtr, QString("Hello and goodbye"));
}

void TestCommentTextParser::stripCommentsNoComment()
{
    testStr = "Hello and goodbye";
    *testPtr = testStr;
    notesPtr->clear();
    pointy::stripComments(testPtr, notesPtr);
    QCOMPARE(*testPtr, QByteArray("Hello and goodbye"));
    QCOMPARE(*notesPtr, QString());

}

void TestCommentTextParser::stripCommentsMultiComment()
{
    testStr = "Hello #and #goodbye";
    *testPtr = testStr;
    notesPtr->clear();
    pointy::stripComments(testPtr, notesPtr);
    QCOMPARE(*testPtr, QByteArray("Hello "));
    QCOMPARE(*notesPtr, QString("and #goodbye"));
}

void TestCommentTextParser::stripCommentsEscaped()
{
    testStr = "Hello \\#and \\#and #goodbye";
    *testPtr = testStr;
    notesPtr->clear();
    pointy::stripComments(testPtr, notesPtr);
    QCOMPARE(*testPtr, QByteArray("Hello #and #and "));
    QCOMPARE(*notesPtr, QString("goodbye"));
}


void TestCommentTextParser::stripCommentsFile()
{
    QFile file(":/test_input_files/comment_test_file.pin");
    if (!file.open(QIODevice::ReadOnly)) {
        qFatal("Slide file can not be read");
    }
    notesPtr->clear();
    while (!file.atEnd())
    {
        testStr = file.readLine();
        *testPtr = testStr;
        pointy::stripComments(testPtr, notesPtr);
    }
    QCOMPARE(*testPtr, QByteArray("Hello #and #and "));
    QCOMPARE(*notesPtr, QString(" Here is a note\ngoodbye\n"));

}

void TestCommentTextParser::stripCommentsEscapedOutofRange()
{
    testStr = "Hello \\# and \\#";
    *testPtr = testStr;
    notesPtr->clear();
    pointy::stripComments(testPtr, notesPtr);
    QCOMPARE(*testPtr, QByteArray("Hello # and #"));
    QCOMPARE(*notesPtr, QString());
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

TestMaxLineLength::TestMaxLineLength()
{
    linePtr = QSharedPointer<QByteArray>(new QByteArray);
    lineLength = 0;

}

void TestMaxLineLength::checkLineLength()
{
    linePtr->append("Hi there!");
    pointy::findMaxLineLength(linePtr, lineLength);
    QCOMPARE(lineLength, int(9));
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
