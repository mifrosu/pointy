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
        if (fontPixelSize * maxLineLength > slideWidth) {
            return slideWidth / maxLineLength;
        }
        else {
            return fontPixelSize * scaleFactor;
        }
    }
    property double padding: { scaleFont/2; }

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

    Rectangle {
        id: slideTextBackground;
        color: shadingColor;
        opacity: {
            if (slideTextData.text === "") {
                return 0;
            }
            else {
                return shadingOpacity;
            }
        }

        height: {slideTextData.height+padding;}
        width: {slideTextData.width+padding;}

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
        id: slideTextData;
        anchors.centerIn: slideTextBackground;
        text: slideText;
        color: textColor;
        font.family: fontFamily;
        font.pixelSize: {
            scaleFont;
        }
        font.pointSize: 1;
        textFormat: {
            (useMarkup === true)? Text.AutoText : Text.PlainText;

        }

    }



}

