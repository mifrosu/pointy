import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0

Rectangle {
    id: mainView;
    width: 400; height: 300;
    property bool notesVisable: true;
    property bool horizontalLayout: true;



    ListView {
        id: dataView;
        //interactive: false;
        snapMode: ListView.SnapToItem;
        width: parent.width; height: parent.height;
        anchors.fill: parent;
        keyNavigationWraps: true;
        highlightFollowsCurrentItem: true;
        highlightRangeMode: "StrictlyEnforceRange";
        highlightMoveDuration: 0;
        orientation: {
            (mainView.horizontalLayout) ? Qt.Horizontal : Qt.Vertical;
        }

        model: slideShow;
        // To visualize data, bind the view's model property to a model
        // and the delegate property to a component

        delegate: PointySlide {
            slideWidth: mainView.width;
            slideHeight: mainView.height;
        }

        Rectangle {
            id: fadeRectangle;
            width: mainView.width; height: mainView.height;
            color: dataView.currentItem.pointyStageColor;
            opacity: 0.0;
        }

        Timer {
            id: waitTime;
            interval: 500;
            repeat: false;
        }

        function loadTransition(pointyTransition) {
            if (pointyTransition === "fade") {
                animateFade.start();
            }
            else {
                return;
            }
        }

        SequentialAnimation  {
            id: animateFade;
            NumberAnimation {
                target: fadeRectangle;
                properties: "opacity";
                from: 0.0; to: 0.3; duration: 0;
            }
//            ScriptAction {
//                script: {
//                    dataView.currentIndex +=1;
//                }
//            }

            NumberAnimation {
                target: fadeRectangle;
                properties: "opacity";
                from: 0.3; to: 0.0; duration: 500;
            }
            running: true;
        }

        property int slideCount: count;

        currentIndex: {
            if (slideCount > 0) {
                return 1;
            } else {
                return 0;
            }
        }

        MouseArea {
            id: mouseArea;
            anchors.fill: parent;
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                if (mouse.button === Qt.LeftButton) {
                    console.log("Left!")
                }
                else {
                    console.log("Right")
                }
            }
        }


        focus: true;
        Keys.onPressed: {
            if (event.key === Qt.Key_Space && (currentIndex < slideCount -1)) {
                loadTransition(dataView.currentItem.pointyTransition);
                currentIndex += 1;
            }
            else if (event.key === Qt.Key_Backspace && currentIndex > 1) {
                loadTransition(dataView.currentItem.pointyTransition);
                currentIndex -=1;

            }
        }

    }
    Window {
        id: notesTextWindow;
        width: 400; height: 300;

        title: "Pointy Notes"
        visible: mainView.notesVisable;

        Text {
            anchors.fill: parent
            anchors.margins: parent.height * 0.1;

            font.pixelSize: 16
            wrapMode: Text.WordWrap

            property string notes: dataView.currentItem.pointyNotes;
            text: notes == "" ? "This slide has no notes." : notes;
            font.italic: notes == "";
        }
    }
}


