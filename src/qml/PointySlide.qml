/*  
 *  This file is part of Pointy.
 *
 *  Copyright (C) 2013 Michael O'Sullivan 
 *
 *  Pointy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Pointy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Pointy.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Written by: Michael O'Sullivan
 */


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
    property string pointyTextAlign: textAlign;
    property double scaleFactor: 1;
    property bool isMediaSlide: false;
    property bool isCommandSlide: false;
    property string commandOut;

    property int scaleFont: {
        if (0.5 * fontPixelSize * maxLineLength > slideWidth) {
        //if (slideTextData.contentWidth > slideWidth) {
            return 2 * slideWidth / maxLineLength;
        }
        else {
            return fontPixelSize * scaleFactor;
        }
    }
    property double padding: { scaleFont/2; }

    width: slideWidth;
    height: slideHeight;
    color: pointyStageColor;
    //color: backgroundColor;
    opacity: pointyOpacity;


    Component {
        // encapsulates element, only loaded when required
        id: slideImage;
        Rectangle {
            width: slideElement.width;
            height: slideElement.height;
            color: {
                if (pointyStageColor != "") {
                return pointyStageColor;
                }
            }
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


                fillMode: {
                    // fill|fit|stretch|unscaled
                    if (backgroundScale === "fit") {
                        Image.PreserveAspectFit;
                    }
                    else if (backgroundScale === "fill") {
                        Image.PreserveAspectCrop;
                    }
                    else if (backgroundScale === "stretch") {
                        Image.Stretch;
                    }
                    else if (backgroundScale === "unscaled")
                    {
                        Image.Pad;
                    }

                }

            }
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

                fillMode: {

                    if (backgroundScale === "fill") {
                        VideoOutput.PreserveAspectCrop;
                    }
                    else if (backgroundScale === "stretch") {
                        VideoOutput.Stretch;
                    }
                    else
                    {
                        VideoOutput.PreserveAspectFit;
                    }

                }

                function playToggle() {
                    if (video.playbackState !== MediaPlayer.PlayingState)
                    {
                        playControl.z = video.z-1;
                        video.play();
                    }
                    else {
                        playControl.z = video.z+1;
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
            fillMode: {
                // fill|fit|stretch|unscaled
                if (backgroundScale === "fit") {
                    Image.PreserveAspectFit;
                }
                else if (backgroundScale === "fill") {
                    Image.PreserveAspectCrop;
                }
                else if (backgroundScale === "stretch") {
                    Image.Stretch;
                }
                else if (backgroundScale === "unscaled")
                {
                    Image.Pad;
                }

            }
        }
    }

    Component {
        id: commandComponent;
        TextInput {
            id: commandField;
            function playToggle() {
                console.log(commandField.text);
                slideElement.commandOut = commandField.text;
            }
            color: "white";
            text: command;
            font.pixelSize: scaleFont;
            font.family: "Monospace";
            parent: slideElement;
            anchors.bottom: parent.bottom;
            anchors.horizontalCenter: parent.horizontalCenter;
//            Keys.onPressed: {
//                if (event.key === Qt.Key_Return) {
//                    playToggle();

//                }
//            }
            Rectangle {
                width: parent.width;
                height: parent.height;
                border.color: "white";
                color: "black";
                z: parent.z-1;
                opacity: 0.3;
            }

        }


    } // component

    Loader {
        id: loadedComponent
        sourceComponent: {
            if (slideMedia.match(
              /.avi|.flv|.mkv|.mov|.mp4|.mpeg|.ogv|.webm/i)) {
                slideElement.isMediaSlide = true;
                return videoComponent;
            }
            else if (slideMedia.match(/.gif/i)) {
                return animatedComponent;
            }
//            else if (command !== "") {
//                slideElement.isCommandSlide = true;
//                return commandComponent;
//            }

            else {
                return slideImage;
            }
        }


    }

    Loader {
        id: commandLoader
        sourceComponent: {
            if (command !== "") {
                slideElement.isCommandSlide = true;
                return commandComponent;
            }
        }
    }

    onMediaSignal: {
        if (slideElement.isCommandSlide === true) {
            commandLoader.item.playToggle();
        }
        else {
            loadedComponent.item.playToggle();
        }


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

        height: {slideTextData.contentHeight + padding;}
        width: {slideTextData.contentWidth + padding;}

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
        //parent: slideTextBackground;
        anchors.centerIn: slideTextBackground;
        text: slideText;
        color: textColor;
        font.family: fontFamily;
        font.pixelSize: {
            scaleFont;
        }
        font.pointSize: 1;
        width: slideTextBackground.width;
        horizontalAlignment: {
            if (pointyTextAlign == "left") {
                return Text.AlignLeft;
            }
            else if (pointyTextAlign == "right") {
                return Text.AlignRight;
            }
            else if (pointyTextAlign == "justify") {
                return Text.AlignJustify;
            }
            else {
                Text.AlignHCenter;
            }
        }

        textFormat: {
            (useMarkup === true)? Text.AutoText : Text.PlainText;

        }

    }



}

