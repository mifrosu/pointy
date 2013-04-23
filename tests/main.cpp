#include <QtTest/QtTest>
#include "pointy_text_parse_tests.h"

int main()
{
    TestTextParser testParser;
    QTest::qExec(&testParser);

    return 0;

}


