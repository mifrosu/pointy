#ifndef POINTY_TEST_FILE_READ_H
#define POINTY_TEST_FILE_READ_H

#include <QtTest/QtTest>
#include "../src/slide_list_model.h"
#include <qsharedpointer.h>

namespace pointy {

class TestFileRead : public QObject
{
    Q_OBJECT
public:
    TestFileRead();

private:
    QSharedPointer<SlideListModel> testModel;
    
private slots:
    void readSimpleFile();

    
};

}

#endif // POINTY_TEST_FILE_READ_H
