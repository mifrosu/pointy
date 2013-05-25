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


#ifndef POINTY_TEXT_PARSE_TESTS_H
#define POINTY_TEXT_PARSE_TESTS_H

#include <QtTest/QtTest>

class TestCommentTextParser: public QObject
{
    Q_OBJECT

public:
    TestCommentTextParser();

private:
    int lineCount;
    QByteArray testStr;
    QSharedPointer<QByteArray> testPtr;
    QSharedPointer<QString> notesPtr;

private slots:
    void stripCommentsMiddle();
    void stripCommentsStart();
    void stripCommentsNoComment();
    void stripCommentsMultiComment();
    void stripCommentsEscaped();
    void stripCommentsFile();
    void stripCommentsEscapedOutofRange();
};

class TestSquareBracketParser: public QObject
{
    Q_OBJECT
public:
    TestSquareBracketParser();

private:
    QSharedPointer<QByteArray> linePtr;
    QSharedPointer<QStringList> storePtr;
    QSharedPointer<int> lineCountPtr;

private slots:
    void stripSquareBracketsNoBrackets();
    void stripSquareBracketsOneSetting();
    void stripSquareBracketsThreeSettings();
    void stripSquareBracketsSettingsWithJunk();
    void stripSquareBracketsMalformedStart();
    void stripSquareBracketsMalformedEnd();

};

class TestMaxLineLength: public QObject
{
    Q_OBJECT
public:
    TestMaxLineLength();

private:
    QSharedPointer<QByteArray> linePtr;
    int lineLength;

private slots:
    void checkLineLength();

};



#endif // POINTY_TEXT_PARSE_TESTS_H
