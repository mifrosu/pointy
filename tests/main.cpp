#include <QtTest/QtTest>
#include "pointy_text_parse_tests.h"
#include "pointy_test_file_read.h"
#include "pointy_test_slide_setting.h"

int main()
{
    TestCommentTextParser testCommentStripParser;
    QTest::qExec(&testCommentStripParser);

    TestSquareBracketParser testSquareBracketParser;
    QTest::qExec(&testSquareBracketParser);

    TestPopulateMapParser popMapParser;
    QTest::qExec(&popMapParser);

    pointy::TestSlideSetting testSlideSetting;
    QTest::qExec(&testSlideSetting);

    pointy::TestFileRead testFileRead;
    QTest::qExec(&testFileRead);

    return 0;

}


