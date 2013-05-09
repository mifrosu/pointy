#include "pointy_test_file_read.h"

namespace pointy {

TestFileRead::TestFileRead()
{
    testModel = QSharedPointer<SlideListModel>(new SlideListModel);
}

void TestFileRead::readSimpleFile()
{
    testModel->readSlideFile(":/test_input_files/simple_file.pin");
    QString data = testModel->getRawSlideData();
    QString expectedData("backgroundScaling: fill\n"
                         "duration: 5.000000\n"
                         "font: Sans 50px\n"
                         "backgroundScaling: fit\n"
                         "slideText: A new slide\n"
                         "backgroundColor: blue\n"
                         "font: Sans 20px\n"
                         "slideText: A blue slide\n"
                         "slideText: A third slide,\n"
                         "with a second line!");
    QCOMPARE(data.trimmed(), expectedData);
}

} // namespace pointy
