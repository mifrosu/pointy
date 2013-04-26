#include <QtTest/QtTest>
#include "pointy_text_parse_tests.h"

int main()
{
    TestCommentTextParser testCommentStripParser;
    QTest::qExec(&testCommentStripParser);

    TestSquareBracketParser testSquareBracketParser;
    QTest::qExec(&testSquareBracketParser);

    TestPopulateMapParser popMapParser;
    QTest::qExec(&popMapParser);

    return 0;

}


