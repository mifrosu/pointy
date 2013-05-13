#include "slide_data.h"
#include "slide_list_model.h"
#include <qdebug.h>
#include <iostream>


int main(int argc, char* argv[])
{
        if (argc > 1) {
            std::cout << "argv: " << argv[1] <<std::endl;
            QString fileName = argv[1];
            pointy::SlideListModel showModel;
            showModel.readSlideFile(fileName);
            QStringList slideData = showModel.getRawSlideData();
            QStringList::const_iterator iter = slideData.begin();
            QStringList::const_iterator endIter = slideData.end();
            while (iter != endIter) {
                qDebug() <<  iter->toLatin1();
                ++iter;
            }
        }
    std::cout << "-----Completed-----"
                 << std::endl;

    return 0;
}
