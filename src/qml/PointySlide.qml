import QtQuick 2.0
import QtMultimedia 5.0

Rectangle {
    id: slideElement;
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

    Component {
        // encapsulates element, only loaded when required
        id: slideImage;
        Image {
            width: slideElement.width;
            height: slideElement.height;

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
    }



    Component {
        id: videoComponent;
        Video {
            id: video;
            width : slideElement.width;
            height : slideElement.height;
            source: { currentPath.currentDir + slideMedia; }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    video.play()
                }
            }

            focus: true
            Keys.onSpacePressed: video.playbackState ===
                                 MediaPlayer.PlayingState ? video.pause()
                                                          : video.play()
            Keys.onLeftPressed: video.seek(video.position - 5000)
            Keys.onRightPressed: video.seek(video.position + 5000)
        }

    }

    Component {
        id: animatedComponent;
        AnimatedImage {
            width : slideElement.width;
            height : slideElement.height;
            source: { currentPath.currentDir + slideMedia; }
        }
    }

    Loader {
        sourceComponent: {
            if (slideMedia.match(/.jpeg|.jpg/i)) {
                return slideImage;
            }
            else if (slideMedia.match(
              /.avi|.flv|.mkv|.mov|.mp4|.mpeg|.ogv|.webm/i)) {

                return videoComponent;
            }
            else if (slideMedia.match(/.gif/i)) {
                return animatedComponent;
            }
        }
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

