import QtQuick 2.0

Item {
    property int slideWidth;
    property int slideHeight;
    width: slideWidth;
    height: slideHeight;

    Rectangle {
        color: backgroundColor;
        anchors.fill: parent;
        width: parent.width;
        height: parent.height;


        Image {
            id: slideImage;
            width: parent.width;
            height: parent.height;


            source: {
                if (slideMedia != "") {
                    return currentPath.currentDir + slideMedia;
                }
                else {
                    return "blank.png";
                }
            }
            fillMode: Image.PreserveAspectFit;
        }

        Text {
            text: slideText;
            color: textColor;
        }
    }
    property string pointyNotes: notesText;


}

