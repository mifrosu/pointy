#include "pointy_test_file_read.h"

namespace pointy {

TestFileRead::TestFileRead()
{
    testModel = QSharedPointer<SlideListModel>(new SlideListModel);
}

void TestFileRead::readSimpleFile()
{
    testModel->readSlideFile(":/test_input_files/simple_file.pin");
    QStringList data = testModel->getRawSlideData();
    QStringList expectedData = (QStringList() << "stageColor: black" <<
                         "font: Sans 50px" <<
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
                         "slideMedia: " <<
                         "backgroundColor: white" <<
                         "slideNumber: 0" <<
                         "stageColor: black" <<
                         "font: Sans 50px" <<
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
                         "slideMedia: " <<
                         "backgroundColor: white" <<
                         "slideNumber: 0" <<
                         "stageColor: black" <<
                         "font: Sans 20px" <<
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
                         "slideMedia: " <<
                         "backgroundColor: blue" <<
                         "slideNumber: 0" <<
                         "stageColor: black" <<
                         "font: Sans 50px" <<
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
                         "slideMedia: " <<
                         "backgroundColor: white" <<
                         "slideNumber: 0");
    QStringList::const_iterator dataIter;
    QStringList::const_iterator dataEnd = data.end();
    QStringList::const_iterator expectedIter;

    while (dataIter != dataEnd) {
        QCOMPARE(dataIter, expectedIter);
        ++dataIter;
        ++expectedIter;
    }
    QCOMPARE(data,expectedData);
}

} // namespace pointy
