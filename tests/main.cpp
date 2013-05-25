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
#include "pointy_test_file_read.h"
#include "pointy_test_slide_setting.h"

#include <QtTest/QtTest>
#include <QtQuickTest/quicktest.h>


int main()
{
    TestCommentTextParser testCommentStripParser;
    QTest::qExec(&testCommentStripParser);

    TestSquareBracketParser testSquareBracketParser;
    QTest::qExec(&testSquareBracketParser);

    TestMaxLineLength testMaxLineLength;
    QTest::qExec(&testMaxLineLength);

    pointy::TestSlideSetting testSlideSetting;
    QTest::qExec(&testSlideSetting);

    pointy::TestFileRead testFileRead;
    QTest::qExec(&testFileRead);





    return 0;

}


