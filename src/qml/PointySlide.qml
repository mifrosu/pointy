import QtQuick 2.0

Rectangle {
    property int slideWidth;
    property int slideHeight;
    property string pointyNotes: notesText;
    property string pointyStageColor: stageColor;
    property string pointyTransition: transitionType;
    property double pointyOpacity: 1.0;
    property string textPosition: position;
    property double scaleFactor: 1;

    property int scaleFont: {
        fontPixelSize * scaleFactor;
    }
    property double padding: { scaleFont/2; }

    width: slideWidth;
    height: slideHeight;
    color: backgroundColor;
    opacity: pointyOpacity;

    Rectangle {
        anchors.fill: parent;
        color: stageColor;
    }


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
        id: slideTextDataFirstPass;
        anchors.centerIn: slideTextBackground;
        text: slideText;
        color: "transparent";
        font.family: fontFamily;
        font.pixelSize: {
            scaleFont;
        }
        font.pointSize: 1;
//        width: {
//            (implicitWidth > (slideWidth-(0.04*parent.width))) ?
//                        slideWidth-(0.04*parent.width) : undefined;
//        }
    }

    Rectangle {
        id: slideTextBackground;
        color: shadingColor;
        opacity: {
            if (slideTextDataFirstPass.text === "") {
                return 0;
            }
            else {
                return shadingOpacity;
            }
        }

        height: {slideTextDataSecondPass.height+padding;}
        width: {slideTextDataSecondPass.width+padding;}

        anchors.margins: {0.02 * parent.width}

        anchors.left: {
            if (position === "left" || position === "top-left" ||
                    position === "bottom-left") {
                return parent.left;
            }
            else {
                return undefined;
            }
        }

        anchors.right: {
            if (position === "right" || position === "top-right" ||
                    position === "bottom-right") {
                return parent.right;
            }
            else {
                return undefined;
            }
        }
        anchors.top: {
            if (position === "top-left" || position === "top" ||
                    position === "top-right") {
                return parent.top;
            }
            else {
                return undefined;
            }
        }
        anchors.bottom: {
            if (position === "bottom-left" ||
                    position === "bottom" ||
                    position === "bottom-right") {
                return parent.bottom;
            }
            else {
                return undefined;
            }
        }
        anchors.centerIn: {
            if (position === "center") {
                return parent.Center;
            }
            else {
                return undefined;
            }
        }
        anchors.horizontalCenter: {
            if (position === "top" || position === "center" ||
                    position === "bottom") {
                return parent.horizontalCenter;
            }
            else {
                return;
            }
        }
        anchors.verticalCenter: {
            if (position === "left" || position === "center" ||
                    position === "right") {
                return parent.verticalCenter;
            }
            else {
                return;
            }
        }
    }


    Text {
        id: slideTextDataSecondPass;
        anchors.centerIn: slideTextBackground;
        text: slideText;
        color: textColor;
        font.family: fontFamily;
        font.pixelSize: {
            scaleFont;
        }
        font.pointSize: 1;
        width: {
            (implicitWidth > (slideWidth-(0.04*parent.width))) ?
                        slideWidth-(0.04*parent.width) : undefined;
        }
        //wrapMode: Text.Wrap;
    }



}

