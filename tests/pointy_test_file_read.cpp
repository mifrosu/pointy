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


#include "pointy_test_file_read.h"

namespace pointy {

TestFileRead::TestFileRead()
{
    testModel = QSharedPointer<SlideListModel>(new SlideListModel);
}

void TestFileRead::readSimpleFile()
{
    testModel->readSlideFile(":/test_input_files/simple_file.pin");
//    QString commentSection("Altering this file will break "
//                           "TestFileRead::readSimpleFile()\n"
//                           " comments with a hash\n"
//                           " global settings before first slide");
    QStringList data = testModel->getRawSlideData();
    QStringList expectedData = (QStringList() <<
//                                "stageColor: black" <<
//                                "font: sans" <<
//                                "fontSize: 50" <<
//                                "fontSizeUnit: px" <<
//                                "notesFont: Sans" <<
//                                "notesFontSize: black" <<
//                                "textColor: white" <<
//                                "textAlign: left" <<
//                                "shadingColor: black" <<
//                                "shadingOpacity: 0.66" <<
//                                "duration: 5.5" <<
//                                "command: " <<
//                                "transition: fade" <<
//                                "cameraFrameRate: 0" <<
//                                "backgroundScale: fill" <<
//                                "position: center" <<
//                                "useMarkup: 1" <<
//                                "slideText: " <<
//                                "maxLineLength: 0" <<
//                                "slideMedia: " <<
//                                "backgroundColor: white" <<
//                                "notesText: " <<
//                                "slideNumber: 0" <<
                                "stageColor: black" <<
                                "font: sans" <<
                                "fontSize: 50" <<
                                "fontSizeUnit: px" <<
                                "notesFont: Sans" <<
                                "notesFontSize: black" <<
                                "textColor: white" <<
                                "textAlign: left" <<
                                "shadingColor: black" <<
                                "shadingOpacity: 0.66" <<
                                "duration: 5.5" <<
                                "command: " <<
                                "transition: fade" <<
                                "cameraFrameRate: 0" <<
                                "backgroundScale: fit" <<
                                "position: center" <<
                                "useMarkup: 1" <<
                                "slideText: A new slide" <<
                                "maxLineLength: 11" <<
                                "slideMedia: " <<
                                "backgroundColor: white" <<
                                "notesText: An initial slide" <<
                                "slideNumber: 0" <<
                                "stageColor: black" <<
                                "font: sans" <<
                                "fontSize: 20" <<
                                "fontSizeUnit: px" <<
                                "notesFont: Sans" <<
                                "notesFontSize: black" <<
                                "textColor: white" <<
                                "textAlign: left" <<
                                "shadingColor: black" <<
                                "shadingOpacity: 0.66" <<
                                "duration: 5.5" <<
                                "command: " <<
                                "transition: fade" <<
                                "cameraFrameRate: 0" <<
                                "backgroundScale: fill" <<
                                "position: center" <<
                                "useMarkup: 1" <<
                                "slideText: A blue slide" <<
                                "maxLineLength: 12" <<
                                "slideMedia: " <<
                                "backgroundColor: lightsteelblue" <<
                                "notesText: Some colour!" <<
                                "slideNumber: 0" <<
                                "stageColor: black" <<
                                "font: sans" <<
                                "fontSize: 50" <<
                                "fontSizeUnit: px" <<
                                "notesFont: Sans" <<
                                "notesFontSize: black" <<
                                "textColor: white" <<
                                "textAlign: left" <<
                                "shadingColor: black" <<
                                "shadingOpacity: 0.66" <<
                                "duration: 5.5" <<
                                "command: " <<
                                "transition: fade" <<
                                "cameraFrameRate: 0" <<
                                "backgroundScale: fill" <<
                                "position: center" <<
                                "useMarkup: 1" <<
                         "slideText: A third slide,\nwith a second line!" <<
                                "maxLineLength: 19" <<
                         "slideMedia: " <<
                         "backgroundColor: white" <<
                         "notesText: a little extra something" <<
                         "slideNumber: 0");
    QStringList::const_iterator dataIter= data.begin();
    QStringList::const_iterator dataEnd = data.end();
    QStringList::const_iterator expectedIter = expectedData.begin();
    QStringList::const_iterator expectedEnd = expectedData.end();

    while (dataIter != dataEnd && expectedIter != expectedEnd) {
        {
            QCOMPARE(*dataIter, *expectedIter);
            ++dataIter;
            ++expectedIter;
        }

    }
    QCOMPARE(data,expectedData);
}

} // namespace pointy
