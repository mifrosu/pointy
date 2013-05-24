import QtQuick 2.0
import QtMultimedia 5.0

Rectangle {
    id: slideElement;
    signal mediaSignal();
    signal backMedia();
    signal forwardMedia();

    property int slideWidth;
    property int slideHeight;
    property string pointyNotes: notesText;
    property string pointyStageColor: stageColor;
    property string pointyTransition: transitionType;
    property double pointyOpacity: 1.0;
    property string textPosition: position;
    property double scaleFactor: 1;
    property bool isMediaSlide: false;

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

                Image {
                    id: playControl;
                    source: "play_control.svg";
                    width: 100
                    height: 75
                    anchors.centerIn: parent;
                    visible: true;
                    antialiasing: true;
                }



                width : slideElement.width;
                height : slideElement.height;

                source: { currentPath.currentDir + slideMedia;}

                function playToggle() {
                    if (video.playbackState !== MediaPlayer.PlayingState)
                    {
                        playControl.visible = false;
                        video.play();
                    }
                    else {
                        playControl.visible = true;
                        video.pause();
                    }
                }

                function forwardSeek() {
                    video.seek(video.position + 2000);  // 2000 msec
                }

                function backwardSeek() {
                    video.seek(video.position - 2000);
                }




                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
                        playToggle();
                    }
                }

                Keys.onPressed: {
                    if (event.key === Qt.Key_Space) {
                        playToggle();

                    }
                }
                Keys.onLeftPressed: video.seek(video.position - 5000);
                Keys.onRightPressed: video.seek(video.position + 5000);
            } // video

    } // component


    Component {
        id: animatedComponent;
        AnimatedImage {
            width : slideElement.width;
            height : slideElement.height;
            source: { currentPath.currentDir + slideMedia; }
        }
    }

    Loader {
        id: loadedComponent
        sourceComponent: {
            if (slideMedia.match(/.jpeg|.jpg/i)) {
                return slideImage;
            }
            else if (slideMedia.match(
              /.avi|.flv|.mkv|.mov|.mp4|.mpeg|.ogv|.webm/i)) {
                slideElement.isMediaSlide = true;
                return videoComponent;
            }
            else if (slideMedia.match(/.gif/i)) {
                return animatedComponent;
            }
        }

    }

    onMediaSignal: {
        loadedComponent.item.playToggle();
    }

    onBackMedia: {
        loadedComponent.item.backwardSeek();
    }

    onForwardMedia: {
        loadedComponent.item.forwardSeek();
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

