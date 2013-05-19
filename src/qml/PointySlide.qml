import QtQuick 2.0

Rectangle {
    property int slideWidth;
    property int slideHeight;
    property string pointyNotes: notesText;
    property string pointyStageColor: stageColor;
    property string pointyTransition: transitionType;
    property double pointyOpacity: 1.0;

    width: slideWidth;
    height: slideHeight;
    color: backgroundColor;
    opacity: pointyOpacity;

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

