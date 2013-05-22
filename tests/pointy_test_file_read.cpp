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
    QStringList expectedData = (QStringList() << "stageColor: black" <<
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
                                "slideText: " <<
                                "maxLineLength: 0" <<
                                "slideMedia: " <<
                                "backgroundColor: white" <<
                                "notesText: " <<
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
